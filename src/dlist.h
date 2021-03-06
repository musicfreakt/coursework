/*
    Библиотека для работы с двусвязным списком.
    
    ---
    Доступные операции:
    push - добавление в начало
    append - добавление в конец
    get - получение произвольного элемента
    insert - вставка в произвольную позицию
    pop - удаление элемента из произвольной позиции
    length - длина списка
    is_empty - проверка на пустоту списка
    swap - поменять местами два элемента
    sort - сортирока
    search - поиск
    reverse - разворот
    shuffle - рандомное перемешивание
*/

#ifndef DLIST_H
#define DLIST_H

// ------------------------- Структуры -------------------------

struct list_info
/*
    Информационная структура списка
*/
{
    char *artist; // Адрес начала строки,
    // которая содержит имя исполнителя
    char *title; // Адрес начала строки, 
    // которая содержит название музыкальной композиции
    char *album; // Адрес начала строки,
    // которая содержит название альбома
    int genre; // Номер жанра музыки
    int year; // Год создания
    int number; // Номер в альбоме
};


struct list_node
/*
    Структура узла списка
*/
{
    struct list_info data; // данные карточки
    struct list_node *next; // указатель на следующий элемент списка
    struct list_node *previous; // указатель на предыдущий элемент списка
};

struct list
/*
    Структура списка
*/
{
    int size; // размер списка
    struct list_node *head; // указатель на первый элемент списка
    struct list_node *tail; // указатель на последний элемент списка
};

typedef struct list LIST;
typedef struct list_node NODE;
typedef struct list_info TRACK;

// ------------------------- Прототипы функций для списка -------------------------
char compare_artist(TRACK, TRACK);
char compare_title(TRACK, TRACK);
char compare_album(TRACK, TRACK);
char compare_number(TRACK, TRACK);
char compare_year(TRACK, TRACK);
char compare_genre(TRACK, TRACK);

LIST *create_list();
void memory_clear(TRACK *t);
void delete_list(LIST **);
void soft_delete_list(LIST **);
void push(LIST* list, TRACK data);
void append(LIST *, TRACK);
NODE *get(LIST *, unsigned);
void insert(LIST *, TRACK, unsigned);
void pop(LIST *, unsigned);
void swap(LIST *, unsigned, unsigned);
char sort_compare(NODE *, NODE *, unsigned);
void sort(LIST *, int);
LIST *search(LIST*, TRACK, char(*compare)(TRACK, TRACK));
void reverse (LIST *);
void shuffle (LIST *);
int length(LIST *);
char is_empty(LIST *);
void print_list(LIST *);
void print_list_element(int, NODE *);
void save_list(LIST *, char *);
TRACK fill_node(char **);
char **simple_split(char *, int, char);
void get_list(LIST*, char*, char);

#endif
