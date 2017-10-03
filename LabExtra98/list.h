#ifndef LIST_H
#define LIST_H


struct Node {
    /** Node's key */
    int key;
    /** Next item on the list */
    struct Node *next;
    /** Past item on the list */
    struct Node *previous;
};

typedef struct Node Node;


/**
* Attempts to insert key on the list.
*
* Returns   -1  if couldn't allocate memory for new item,
*            1  if inserted item successfully.
*/
int insert_on_end(Node **list, int key);

/**
* Retrieves the end of the list.
*
* Returns   NULL    if the list is empty,
*           a pointer to the end of the list if successfully found it.
*/
Node *get_end(Node *list);

/**
* Attempts to remove item from the list.
*/
void remove_from_list(Node **list, int key);

/**
* Empties the list, releasing its allocated memory.
*/
void free_list(Node **list);


#endif /* LIST_H */
