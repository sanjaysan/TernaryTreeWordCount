/**
 * @file wl.h
 * @brief A Ternary Tree Class which stores words from a file and their occurrences
 * @author <a href="mailto:subramanians@wisc.edu">Sanjay Subramanian Seshadri</a>
 * @StudentName Sanjay Subramanian Seshadri 
 * @UWCampusID 9075109588
 * @email <subramanians@wisc.edu>
 * @version 1.0
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <fstream>
//#include <regex>

using namespace std;
//using namespace std::regex_constants;

/**
* @brief A Ternary Tree class which holds words from a file and their occurrences
*
*/

class TernaryTreeNode
{
private:
    char value;
    bool is_leaf;
    int count;
    TernaryTreeNode *left, *equal, *right;
    vector<int> vec;
    int *positions;
    int element_count;
public:

   /**
     * @param value Character to be inserted in the Ternary Search Tree
     * @return Ternary Tree Node with the value populated
     * @brief Creates a new Ternary Tree node and populates it with the passed value
     */
    TernaryTreeNode* createNode(char value)
    {
        TernaryTreeNode* new_node = new TernaryTreeNode;
        if (new_node != NULL)
        {
            new_node -> value = value;
            new_node -> is_leaf = false;
            new_node -> count = 0;
            new_node -> left = new_node -> equal = new_node -> right = NULL;
            new_node -> positions = new int[1];
            new_node -> positions[0] = 0;
            new_node -> element_count = 0;
        }
        return new_node;
    }

    /**
     * @param root Root of the Ternary Search Tree
     * @param word The word to be inserted in the tree
     * @param position The position of the word in the file
     * @brief Inserts a new word in the Ternary Search Tree
     */
    void insert_character(TernaryTreeNode** root, const char *word, int position)
    {
        if (! (*root) )
        {
            *root = createNode(*word);
        }
        if ((isalnum(*word) || (*word) =='\''))
        {
            if ((*word) < (*root)->value)
            {
                insert_character(&((*root)->left), word, position);
            }
            else if ((*word) > (*root)->value)
            {
                insert_character(&((*root)->right), word, position);
            }
            else
            {
                if (*(word + 1) && (isalnum(*word) || (*word) =='\''))
                {
                    insert_character(&((*root)->equal), word + 1, position);
                }
                else
                {
                    (*root)->is_leaf = true;
                    (*root)->vec.push_back(position);
                    

                    /*if ((*root) -> element_count == 0)
                    {
                        (*root) -> positions[(*root) -> element_count++] = position;
                    }
                    else
                    {
                        int *temp = new int [(*root) -> element_count];
                        for (int i = 0; i < (*root) -> element_count; i++)
                        {
                            temp[i] = (*root) -> positions[i];
                        }
                        delete[] (*root) -> positions;
                        (*root) -> positions = new int[(*root) -> element_count + 1];
                        for (int i = 0; i < (*root) -> element_count; i++)
                        {
                            (*root) -> positions[i] = temp[i];
                        }
                        (*root) -> positions[(*root) -> element_count++] = position;
			//delete [] temp;
                    }*/
                }
            }
        }
    }

    /**
     * @param str A word from the input file
     * @return String with all special characters except the apostrophe removed
     * @brief Removes characters other than alphabets, numbers and apostrophe from the word
     */
    string clean_string(string str)
    {
        int i = 0, len = str.length();
        while(i < len)
        {
            char c = str[i];
            if(((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && ( c <= 'z')))
            {
                if((c >= 'A') && (c <= 'Z'))
                {
                    str[i] += 32;
                }
                ++i;
            }
            else
            {
                str.erase(i,1);
                --len;
            }
        }
        return str;
    }

    /**
     * @param root Root of the Ternary Search Tree
     * @param word The word whose nth occurrence has to be found out
     * @param position Specifies position of the nth occurrence to be found out
     * @return The position of the nth occurrence of the word to be found out
     * @brief Searches the given word in the Ternary Search tree and returns its
     * nth (denoted by position) occurrence
     */
    int searchTST(TernaryTreeNode *root, string word, int position)
    {
        if (!root)
        {
            return 0;
        }

        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        const char *c = word.c_str();
        if ( *c < (root)->value)
        {
            return searchTST(root->left, c, position);
        }

        else if (*c > (root)->value)
        {
            return searchTST(root->right, c, position);
        }

        else
        {
            if (*(c + 1) == '\0')
            {
                if (root && root->is_leaf)
                {
                    vector<int>::iterator iter;
                    if (position <= (int) root -> vec.size())
                    {
                        iter = find(root->vec.begin(), root->vec.end(), root->vec.at(position - 1));
                        if (iter == root->vec.end())
                        {
                            return 0;
                        }
                        else
                        {
                            return root->vec.at(position - 1);
                        }
                    }
                    else
                    {
                        return 0;
                    }
                    /*int size = root -> element_count;
                    if (position <= size)
                    {
                        return root -> positions[position - 1];
                    }
		    else
                    {
			return 0;
                    }*/
                }
            }
            return searchTST(root->equal, c + 1, position);
        }
    }

    /**
     * @param root Root of the Ternary Search Tree
     * @param depth Level of the root node
     * @brief Deletes all the nodes in the Ternary Search Tree
     */
    void clean_word_list(TernaryTreeNode* root, int depth)
    {
        if (root)
        {
            clean_word_list(root -> left, depth);

            if (root -> is_leaf)
            {
		//delete [] root -> positions;
                delete root;
            }

            clean_word_list(root -> equal, depth + 1);

            clean_word_list(root -> right, depth);
        }
    }

    /**
     * @param root Root of the Ternary Search Tree
     * @param file_name The name of the file to be read as input
     * @brief Reads words from the input file
     */
    TernaryTreeNode* load_file (TernaryTreeNode *root, char *file_name)
    {
        ifstream in(file_name);
        if (in.is_open())
        {
            string word;
            int word_position = 1;
            //std::regex pattern("[^0-9a-zA-Z']+", ECMAScript);
            //string replacement = "";
            while (in >> word)
            {
                std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                word = root -> clean_string(word);
                root -> insert_character(&root, word.c_str(), word_position++);
            }
        }
        else
        {
            cout << "ERROR: Invalid command" << endl;
        }
        return root;
    }
};

