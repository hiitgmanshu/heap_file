#include <bits/stdc++.h>
using namespace std;

struct page
{
    int page_no;
    map<int, int> record;
    int address_of_previous_page;
    int address_of_next_page;
    int address_of_free_space;
    int count;
    page *prec;
    page *next;
};

page *root = nullptr;
int total_page = 0;

page *init_page()
{
    page *new_page = new page();
    new_page->page_no = total_page;
    new_page->address_of_previous_page = total_page - 1;
    total_page++;
    new_page->address_of_next_page = -1;
    new_page->address_of_free_space = 0;
    new_page->count = 0;
    new_page->prec = nullptr;
    new_page->next = nullptr;
    return new_page;
}

void insert(int Page_size, int record_size, int primary_key)
{
    if (root == nullptr)
    {
        root = init_page();
        root->record.insert(make_pair(primary_key, record_size));
        root->count++;
        root->address_of_free_space = record_size;
        return;
    }
    page *curr = root;
    while (curr != nullptr)
    {

        if ((curr->address_of_free_space) + 16 + (curr->count) * 4 + (record_size + 4) > Page_size)
        {
            if (curr->next == nullptr)
            {
                page *new_page = init_page();
                curr->address_of_next_page = new_page->page_no;
                curr->next = new_page;
                new_page->prec = curr;
                new_page->record.insert(make_pair(primary_key, record_size));
                new_page->count++;
                new_page->address_of_free_space += record_size;
                return;
            }
            else
            {
                curr = curr->next;
            }
        }
        else
        {
            curr->record.insert(make_pair(primary_key, record_size));
            curr->count++;
            curr->address_of_free_space += record_size;
            return;
        }
    }
}

void display()
{
    if (root == nullptr)
    {
        cout << "0" << endl;
        return;
    }
    page *curr = root;
    cout << total_page << " ";
    while (curr != nullptr)
    {
        cout << curr->count << " ";
        curr = curr->next;
    }
    cout << endl;
}

void search(int primary_key)
{
    int slot_no;
    page *curr = root;
    while (curr != nullptr)
    {
        slot_no = 0;
        for (auto x : curr->record)
        {
            if (x.first == primary_key)
            {
                cout << curr->page_no << " " << slot_no << endl;
                return;
            }
            slot_no++;
        }
        curr = curr->next;
    }
    cout << -1 << " " << -1 << endl;
    return;
}

int main()
{
    int size;
    cin >> size;
    int choice;
    int r_size, p_key;
    while (1)
    {
        cin >> choice;
        switch (choice)
        {
        case 1:
            cin >> r_size >> p_key;
            insert(size, r_size, p_key);
            break;
        case 2:
            display();
            break;
        case 3:
            cin >> p_key;
            search(p_key);
            break;
        case 4:
            exit(0);
            break;
        }
    }
}