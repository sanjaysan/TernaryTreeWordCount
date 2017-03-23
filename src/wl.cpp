/**
 * @file wl.cpp
 * @brief The driver program which controls all the function calls
 * @author <a href="mailto:subramanians@wisc.edu">Sanjay Subramanian Seshadri</a>
 * @StudentName Sanjay Subramanian Seshadri 
 * @UWCampusID 9075109588
 * @email <subramanians@wisc.edu>
 * @version 1.0
 */

#include "wl.h"

/**
 * @brief The driver program which controls all the function calls
 */
int main()
{
    TernaryTreeNode *root = NULL;
    string input, line, word, file_name;

    while (true)
    {
        cout << ">";
        getline(std::cin, line);

        char *command[4];
        char **next = command;
        char *new_line = new char[line.size() + 1];
        copy(line.begin(), line.end(), new_line);
        new_line[line.size()] = '\0';

        char *t = strtok(new_line, " \t");
        while (t != NULL)
        {
            *next++ = t;
            t = strtok(NULL," \t");
        }
        *next = NULL;
        delete t;

        if (strcmp(command[0], "end") == 0)
        {
            if (root)
            {
		root = NULL;
                //delete new_line;
                //root->clean_word_list(root, 0);
            }
            break;
        }

        else if (strcmp(command[0], "new") == 0)
        {
            if (root)
            {
                root = NULL;
                //root->clean_word_list(root, 0);
            }
        }

        else if (strcmp(command[0], "load") == 0)
        {
            if (command[1] == NULL)
            {
                cout << "ERROR: Invalid command" << endl;
                continue;
            }
            else
            {
                if (root)
                {
                    root = NULL;
                    //root -> clean_word_list(root, 0);
                }
                root = root -> load_file(root, command[1]);
                if (root == NULL)
                {
                    cout << "ERROR: Invalid command" << endl;
                    continue;
                }
            }
        }
        else if (strcmp(command[0], "locate") == 0)
        {
            bool is_not_a_number = false;
            if (command[1] == NULL || command[2] == NULL)
            {
                cout << "ERROR: Invalid command" << endl;
                continue;
            }
            else
            {
                for (int i = 0; *(command[2] + i); i++)
                {
                    if (!isdigit(*(command[2] + i)))
                    {
                        cout << "ERROR: Invalid command" << endl;
                        is_not_a_number = true;
                        break;
                    }
                }
                if (!is_not_a_number)
                {
                    int result = root->searchTST(root, command[1], atoi(command[2]));
                    if (result != 0)
                    {
                        cout << result << endl;
                    }
                    else
                    {
                        cout << "No matching entry" << endl;
                    }
                }
                else
                {
                    continue;
                }
            }
        }
        else
        {
            cout << "ERROR: Invalid command" << endl;
            continue;
        }
    }
    root -> clean_word_list(root,0);
    return 0;
}
