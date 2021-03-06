#include "menu.h"

TRACK get_music_data()
{
    TRACK music;

    system(CLEAR);
    music.artist = get_string(1);
    music.title = get_string(2);
    music.album = get_string(3);
    music.number = get_number();
    music.year = get_year();
    music.genre = get_genre();

    return music;
}


void print_menu(unsigned char menu, unsigned char *flags)
/*
    Вывод пунктов меню на экран
    ---
    @param char *flags - одномерный массив флагов, для вывода
                         только доступных пунктов меню
*/
{
    switch (menu)
    {
        case MAIN_MENU:
            system(CLEAR);
            puts("Main menu");
            if (flags[1])
                puts("1. Help");
            if (flags[2])
                puts("2. Add music list");
            if (flags[3])
                puts("3. Edit music list");
            if (flags[4])
                puts("4. Search music");
            if (flags[5])
                puts("5. Print music list");
            if (flags[0])
                puts("0. Exit");
        break;
        case INPUT_MENU:
            system(CLEAR);
            puts("Input menu");
            puts("1. Input from term");
            puts("2. Input from file");
            puts("0. Return to Main Menu");
        break;
        case EDIT_MENU:
            system(CLEAR);
            puts("Edit menu");
            puts("1. Edit track info");
            puts("2. Sort music list");
            puts("3. Reverse list");
            puts("4. Random shuffle");
            puts("5. Swap");
            puts("6. Delete track");
            puts("0. Return to Main Menu");
        break;
        case SEARCH_MENU:
            system(CLEAR);
            puts("Choose field to search for");
            if (flags[0] == 1)
                puts("1. Artist");
            if (flags[1] == 1)
                puts("2. Title");
            if (flags[2] == 1)
                puts("3. Album");
            if (flags[3] == 1)
                puts("4. Number in album");
            if (flags[4] == 1)
                puts("5. Year");
            if (flags[5] == 1)
                puts("6. Genre");
        break;
        case OUTPUT_MENU:
            system(CLEAR);
            puts("Output menu");
            puts("1. Print all list");
            puts("2. Print one track");
            puts("3. Save list in file");
            puts("0. Return to Main Menu");
        break;
        case INPUT_TERM_MENU:
            system(CLEAR);
            if (flags[0] == 1)
            {
                puts("1. Add to head");
                puts("2. Add to tail");
                puts("3. Add after n-th element");
            }
        break;
        case EDIT_INFO_MENU:
            puts("\nEdit info menu");
            puts("1. Edit artist");
            puts("2. Edit title");
            puts("3. Edit album");
            puts("4. Edit number in album");
            puts("5. Edit year");
            puts("6. Edit genre");
            puts("0. Return to Edit Menu");
        break;
        case SORT_MENU1:
            system(CLEAR);
            puts("Sort menu");
            puts("1. Sort by artists");
            puts("2. Sort by title");
            puts("3. Sort by album");
            puts("4. Sort by number in album");
            puts("5. Sort by year");
            puts("0. Return to Edit Menu");
        break;
        case SORT_MENU2:
            system(CLEAR);
            puts("1. Increase");
            puts("2. Decrease");
        break;
        case DELETE_MENU:
            system(CLEAR);
            puts("Delete menu");
            puts("1. Delete track by number");
            puts("2. Delete all music list");
            puts("0. Return to Edit Menu");
        break;
    }
    printf(">");
}


void input_menu(LIST *list)
{
    int variant,
        exit_flag;
    char answer;
    unsigned char flag;
    char *path = NULL;

    exit_flag = 1;
    do
    {

        print_menu(INPUT_MENU, NULL);
        save_scanf(&variant);
        
        switch (variant)
        {
            case 1:
                do
                {
                    if (is_empty(list))
                        flag = 0;
                    else
                        flag = 1;

                    if (flag != 0)
                    {
                        do
                        {
                            print_menu(INPUT_TERM_MENU, &flag);
                            save_scanf(&variant);
                            if (variant < 1 || variant > 3)
                                print_msg(MENU_ERROR);
                        }
                        while (variant < 1 || variant > 3);
                    } else
                        variant = 1;
                    
                    if (variant == 1)
                        push(list, get_music_data());
                    else if (variant == 2)
                        append(list, get_music_data());
                    else
                    {
                        if (flag == 1)
                        {
                            do
                            {
                                puts("Enter index of element");
                                printf("Length of you list is: %d\n", length(list));
                                printf(">");
                                save_scanf(&variant);
                                if (variant >= length(list))
                                    puts(INDEX_ERROR);
                            }
                            while (variant >= length(list));
                            if (variant == length(list)-1)
                                append(list, get_music_data());
                            else
                                insert(list, get_music_data(), variant);
                        }
                        else
                            print_msg(MENU_ERROR);
                    }
                    
                    puts("\nDo you want to continue? (y/n)");
                    printf(">");
                    scanf("%c", &answer);
                    clean_stdin();
                }
                while(answer == 'y' || answer == 'Y');
                if (list->head != NULL)
                {
                    print_list(list);
                    pause();
                }
            break;
            case 2:
                system(CLEAR);
                puts("Input filename (default: data.csv)");
                printf(">");
                path = get_string(0);
                get_list(list, path, ';');
                if (list->head != NULL)
                {
                    print_list(list);
                    pause();
                }
                free(path);
                path = NULL;
            break;
            case 0:
                exit_flag = 0;
            break;
            default:
                print_msg(MENU_ERROR);
            break;
        }

    }
    while(exit_flag);
}

void output_menu(LIST *list)
{
    int variant,
        exit_flag,
        n;
    char *path;
    
    exit_flag = 1;
    do
    {
        print_menu(OUTPUT_MENU, NULL);

        save_scanf(&variant);
        switch (variant)
        {
            case 1:
                print_list(list);
                pause();
            break;
            case 2:
                system(CLEAR);
                do
                {
                    puts("Input number of list element");
                    printf("Length of you list is: %d\n", length(list));
                    printf(">");
                    save_scanf(&n);
                    if (n > length(list))
                        puts("Number can't be greater than length");
                }
                while(n > length(list));
                print_list_element(n-1, get(list, n-1));
                pause();
            break;
            case 3:
                system(CLEAR);
                puts("Input filename");
                printf(">");
                path = get_string(0);
                save_list(list, path);
                free(path);
                path = NULL;
            break;
            case 0:
                exit_flag = 0;
            break;
            default:
                print_msg(MENU_ERROR);
            break;
        }

    }
    while(exit_flag);
}

void search_menu(LIST *list)
{
    int variant,
        i;
        
    LIST *search_list = NULL,
         *temp = NULL;

    TRACK search_param;
    char exit_flag;
    unsigned char flags[6];
    
    for (i = 0; i < 6; i++)
        flags[i] = 1;
    
    i = 0;
    search_list = list;
    do
    {
        print_menu(SEARCH_MENU, flags);

        save_scanf(&variant);
        switch (variant)
        {
            case 1:
                if (flags[0] == 1)                    
                {
                    search_param.artist = get_string(1);
                    flags[0] = 0;
                    temp = search_list;
                    search_list = search(search_list, search_param, compare_artist);
                    if (i != 0)
                        soft_delete_list(&temp);
                    i++;
                    free(search_param.artist);
                }
                else
                    print_msg(MENU_ERROR);
            break;
            case 2:
                if (flags[1] == 1)                    
                {
                    search_param.title = get_string(2);
                    flags[1] = 0;
                    temp = search_list;
                    search_list = search(search_list, search_param, compare_title);
                    if (i != 0)
                        soft_delete_list(&temp);
                    i++;
                    free(search_param.title);
                }
                else
                    print_msg(MENU_ERROR);
            break;
            case 3:
                if (flags[2] == 1)                    
                {
                    search_param.album = get_string(3);
                    flags[2] = 0;
                    temp = search_list;
                    search_list = search(search_list, search_param, compare_album);
                    if (i != 0)
                        soft_delete_list(&temp);
                    i++;
                    free(search_param.album);
                }
                else
                    print_msg(MENU_ERROR);
            break;
            case 4:
                if (flags[3] == 1)                    
                {
                    search_param.number = get_number();
                    flags[3] = 0;
                    temp = search_list;
                    search_list = search(search_list, search_param, compare_number);
                    if (i != 0)
                        soft_delete_list(&temp);
                    i++;
                }
                else
                    print_msg(MENU_ERROR);
            break;
            case 5:
                if (flags[4] == 1)                    
                {
                    search_param.year = get_year();
                    flags[4] = 0;
                    temp = search_list;
                    search_list = search(search_list, search_param, compare_year);
                    if (i != 0)
                        soft_delete_list(&temp);
                    i++;
                }
                else
                    print_msg(MENU_ERROR);
            break;
            case 6:
                if (flags[5] == 1)                    
                {
                    search_param.genre = get_genre();
                    flags[5] = 0;
                    temp = search_list;
                    search_list = search(search_list, search_param, compare_genre);
                    if (i != 0)
                        soft_delete_list(&temp);
                    i++;
                }
                else
                    print_msg(MENU_ERROR);
            break;
            default:
                print_msg(MENU_ERROR);
            break;
        }
        
        if(i != 6)
        {
            puts("\nDo you want to choose more param? (y/n)");
            printf(">");
            scanf("%c", &exit_flag);
            clean_stdin();
        }
        else
            exit_flag = 0;
    }
    while(exit_flag == 'Y' || exit_flag == 'y');
    
    if (!is_empty(search_list))
    {
        print_list(search_list);
        pause();
    }
    else
        print_msg(SEARCH_ERROR);

    if (i != 0)
        soft_delete_list(&search_list);
    if (i > 2)
        soft_delete_list(&temp);
}


void edit_menu(LIST **list)
{
    int variant,
        exit_flag,
        first,
        second;

    exit_flag = 1;
    do
    {
        print_menu(EDIT_MENU, NULL);

        save_scanf(&variant);
        switch (variant)
        {
            case 1:
                edit_info_menu(*list);
            break;
            case 2:
                sort_menu(*list);
            break;
            case 3:
                reverse(*list);
                print_list(*list);
                pause();
            break;
            case 4:
                shuffle(*list);
                print_list(*list);
                pause();
            break;
            case 5:
                do
                {
                    print_list(*list);
                    puts("\nInput first number");
                    printf(">");
                    save_scanf(&first);
                    puts("\nInput second number");
                    printf(">");
                    save_scanf(&second);
                    if (first > length(*list) || second > length(*list)
                        || first < 1 || second < 1)
                        print_msg(INDEX_ERROR);
                } while (first > length(*list) || second > length(*list) || first < 1 || second < 1);

                swap(*list, first-1, second-1);
                print_list(*list);
                pause();
            break;
            case 6:
                delete_menu(list);
                
                if (is_empty(*list))
                    exit_flag = 0;
            break;
            case 0:
                exit_flag = 0;
            break;
            default:
                print_msg(MENU_ERROR);
            break;
        }

    }
    while(exit_flag);
}

void edit_info_menu(LIST *list)
{
    int change_int,
        variant1,
        variant2,
        exit_flag;
    
    char *change_str;    
    NODE *temp_node = NULL;
    exit_flag = 1;
    do
    {
        print_list(list);
        puts("\nEnter number of element of list (or 0 to return to Edit Menu)");
        printf(">");
        save_scanf(&variant1);
        if (variant1 == 0)
           exit_flag = 0; 
        else if (variant1 > length(list) || variant1 < 0)
            print_msg("Number should be greater than 0 and less than length");
    }
    while(variant1 > length(list) || variant1 < 0);
    
    while (exit_flag)
    {
        temp_node = get(list, variant1-1);
        print_list_element(variant1-1, temp_node);
        print_menu(EDIT_INFO_MENU, NULL);
        save_scanf(&variant2);
        
        switch (variant2)
        {
            case 1:
                system(CLEAR);
                change_str = get_string(1);
                free(temp_node->data.artist);
                temp_node->data.artist = change_str;
            break;
            case 2:
                system(CLEAR);
                change_str = get_string(2);
                free(temp_node->data.title);
                temp_node->data.title = change_str;
            break;
            case 3:
                system(CLEAR);
                change_str = get_string(3);
                free(temp_node->data.album);
                temp_node->data.album = change_str;
            break;
            case 4:
                system(CLEAR);
                change_int = get_number();
                temp_node->data.number = change_int;
            break;
            case 5:
                system(CLEAR);
                change_int = get_year();
                temp_node->data.year = change_int;
            break;
            case 6:
                system(CLEAR);
                change_int = get_genre();
                temp_node->data.genre = change_int;
            break;
            case 0:
                exit_flag = 0;
            break;
            default:
                print_msg(MENU_ERROR);
            break;
        }
    }
}

void sort_menu(LIST *list)
{
    int type;
    int rev;
    
    do 
    {
        print_menu(SORT_MENU1, NULL);
        save_scanf(&type);
        
        if (type > 0 && type < 6)
        {
            do
            {
                print_menu(SORT_MENU2, NULL);
                save_scanf(&rev);
                if (rev > 2 || rev < 1)
                    print_msg(MENU_ERROR);
            }while(rev > 2 || rev < 1);
        
            sort(list, type);
            if (rev == 2)
                reverse(list);
            print_list(list);
            pause();
            type = 0;
        }
        else if(type != 0)
            print_msg(MENU_ERROR);
    }
    while (type != 0);
}

void delete_menu(LIST **list)
{
    int number,
        variant,
        exit_flag;
        
    exit_flag = 1;
    do
    {
        
        print_menu(DELETE_MENU, NULL);

        save_scanf(&variant);

        switch (variant)
        {
            case 1:
                print_list(*list);
                puts("\nEnter number of element of list");
                printf(">");
                save_scanf(&number);
                pop(*list, number-1);
                if (is_empty(*list))
                    exit_flag = 0;
                else
                {
                    print_list(*list);
                    pause();
                }   
            break;
            case 2:
                delete_list(list);
                print_msg(LIST_DELETE);
                exit_flag = 0;
            break;
            case 0:
                exit_flag = 0;
            break;
            default:
                print_msg(MENU_ERROR);
            break;
        }

    }
    while(exit_flag);
}

void help()
{
    system(CLEAR);
    puts("This program will help you create your music library.\n\n");
    puts("First you need to enter the data in the program.");
    puts("To do this, go to item 2 and select a convenient input method. ");
    puts("After that you will get access to all the features of the program.\n");
    puts("Go to item 3 to edit the list. Features: ");
    puts("1. Edit information in item");
    puts("2. Sort music list");
    puts("3. Reverse music list");
    puts("4. Shuffle music list");
    puts("5. Delete list or item\n");
    puts("Go to item 4 to search.");
    puts("You can search by any number of fields.\n");
    puts("Go to item 5 to output list.");
    puts("There are three methods available to you. You can choose any one.\n");
    puts("Good Luck! \n");
    pause();
}

 
