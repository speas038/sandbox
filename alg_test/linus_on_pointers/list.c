


typedef struct list_entry {
    int val;
    struct list_entry *next;
} list_entry;

list_entry *head;
int to_remove = 5;

int main ()
{
    
    list_entry **pp = &head; /* pointer to a pointer */
    list_entry *entry = head;
    
    while (entry) {
       if (entry->val == to_remove)
               *pp = entry->next;
    
       pp = &entry->next;
       entry = entry->next;
    }

}
