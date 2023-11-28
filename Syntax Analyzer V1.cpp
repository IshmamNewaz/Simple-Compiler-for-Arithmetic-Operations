#include <iostream>

#include <string.h>

using namespace std;

int main() {
  int syntax_tree_root, start_variable, top_rule, left_variable, children_counts, children_index, adjust_variable_replacer_index;
  int input_token_index, statement_index, remove_syntax_tree_prev_value, variable_replacing_matching_value;
  string input_token; //variable for input token
  char statement[7]; //variable to store the token character by characters
  int breaker = 0; //variable for while loop breaker
  //Context free grammar for the given input
  char grammar_rules[6][11] = {
    "A->BCDEDF.",
    "B->i.",
    "C->=.",
    "D->i.",
    "E->+.",
    "F->;."
  };

  char variable_replacer[50]; //Character array for variable replacing
  char syntax_tree[50]; //Character array for syntax tree
  int children_counter[50]; //Character array children counting

  cout << "Enter the input token:";
  getline(cin, input_token); //taking token input

  cout << "The entered token was:" << input_token << endl;

  statement_index = 0;

  //loop to store the tokens (placeholder with id value) into "Statement" array in the for of "i"
  for (input_token_index = 0; input_token_index < input_token.length(); input_token_index++) {
    if (input_token[input_token_index] == '<') {
      statement[statement_index] = input_token[input_token_index + 1];
      statement_index++;
    }
  }
  //assigning loop values to 0;
  syntax_tree_root = 0;
  start_variable = 0;
  top_rule = 0;
  left_variable = 0;
  children_counts = 0;
  children_index = 0;

  //Storing the top most left value (A) from the CFG grammar array
  syntax_tree[syntax_tree_root] = grammar_rules[top_rule][left_variable];
  variable_replacer[start_variable] = grammar_rules[top_rule][left_variable];

  int variable_replacer_current_index = 0;
  int syntax_tree_current_index = 1;
  int statement_matcher_index = 0;

  //Loops to generate syntax tree
  while (true) {

    //Declaration of loop variables
    int grammar_rule_number;
    int rule_right_side_copier_index;
    int copy_flag;

    //Loop for looping all the grammars in the CFG row by row
    for (grammar_rule_number = 0; grammar_rule_number < 7; grammar_rule_number++) {
      //Checks for the grammar_rules and variable_replacer's current index has the same value
      if (grammar_rules[grammar_rule_number][left_variable] == variable_replacer[variable_replacer_current_index]) {
        //Variable used to as an identifier to  if the current index in rules has check '>' 
        copy_flag = 0;
        //loop to loop all the grammer's terminals by column
        for (rule_right_side_copier_index = 0; grammar_rules[grammar_rule_number][rule_right_side_copier_index] != '.'; rule_right_side_copier_index++) {
          //Checks whether the grammar rule current index has '>'
          if (grammar_rules[grammar_rule_number][rule_right_side_copier_index] == '>') {
            copy_flag = 1;
            //conitnue if '>' found
            continue;
          }
          //If copy_flag is 1 then the below will happen:
          //1. values from grammar_rules will be stored inside the syntax_tree
          //2. increase syntax_tree_current_index by 1 for each iteration

          if (copy_flag == 1) {
            syntax_tree[syntax_tree_current_index] = grammar_rules[grammar_rule_number][rule_right_side_copier_index];
            syntax_tree_current_index++;
            //3. count the number of children for the current Rule
            for (int i = 0; grammar_rules[grammar_rule_number][i] != '.'; i++) {
              if (grammar_rules[grammar_rule_number][i] == '>') {
                int new_var = i + 1;
                //loop to keep the count of children of current rule
                for (int k = new_var; grammar_rules[grammar_rule_number][k] != '.'; k++) {
                  children_counts++;
                }
              }

            }
            //4. Stores the counts into the children_counter array
            children_counter[children_index] = children_counts;
            children_counts = 0;
            variable_replacing_matching_value = 1;
            //5. Stroes the contents of the current rule into the variable_replacer
            variable_replacer[variable_replacer_current_index] = grammar_rules[grammar_rule_number][rule_right_side_copier_index];
            //6. Incrase the variable_replacer_current_index by 1 in each iteration
            variable_replacer_current_index++;
            remove_syntax_tree_prev_value = 1;
            adjust_variable_replacer_index = 1;
          }
        }
      }
    }
    int new_index = syntax_tree_current_index;
    //Loop to replace all syntax_tree nonterminal elements with leaf nodes, same goes for variable_replacer array 
    while (true) {
      //loop for visiting all the elements in syntax_tree and variable_replacer
      for (int i = remove_syntax_tree_prev_value; i < new_index; i++) {
        //checks whether the current value matches for syntax_tree matches with variable_replacer
        if (syntax_tree[i] == variable_replacer[i - adjust_variable_replacer_index]) {
          for (int j = 0; j < 6; j++) {
            //checks whther the current grammar nonterminal matches the syntax_trees nonterminal element
            if (grammar_rules[j][0] == syntax_tree[i]) {
              //new variable for keeping count of current index values for syntax array.
              variable_replacing_matching_value = variable_replacing_matching_value + children_counter[children_index];
              //loop to count all the children for current rule
              for (int copier = 0; grammar_rules[j][copier] != '.'; copier++) {
                if (grammar_rules[j][copier] == '>') {
                  int new_var = copier + 1;
                  for (int counter = new_var; grammar_rules[j][counter] != '.'; counter++) {
                    children_counts++;
                  }
                }

              }
              //loop to show the current progress of variable replacer's vaule level by level
              for (int i = 0; i < variable_replacer_current_index; i++) {
                cout << variable_replacer[i] << " ";
              }
              cout << endl;
              //Updates the current value of variable_replacer with grammar_rules terminals/leaf nodes
              variable_replacer[i - adjust_variable_replacer_index] = grammar_rules[j][3];
              //updates the syntax_tree with grammar_rules terminal/leaf nodes
              syntax_tree[variable_replacing_matching_value] = grammar_rules[j][3];
              //incrasing values per each iteration
              syntax_tree_current_index++;
              children_index++;
              children_counter[children_index] = children_counts;
              children_counts = 0;

            }

          }

        }
        remove_syntax_tree_prev_value++;
      }
      break;
    }
    cout << "FINAL RESULT" << endl;
    //for loop to show the final output of variable_replacer array
    for (int i = 0; i < variable_replacer_current_index; i++) {
      cout << variable_replacer[i] << " ";
      //conditional statement to check whether the input follow CFG or not
      if (statement[i] == variable_replacer[i]) {
        breaker = 0;
      } else {
        breaker = 1;
      }
    }
    cout << endl << "SYNTAX TREE" << endl;
    //loop to show the final output of syntax_array
    for (int i = 0; i < syntax_tree_current_index; i++) {
      cout << syntax_tree[i] << " ";
    }

    cout << endl << "CHILDREN COUNTER" << endl;
    //loop to show the children counts for all nonterminal values in syntax_array
    for (int i = 0; i < children_index + 1; i++) {
      cout << children_counter[i] << " ";
    }
    cout << endl;
    //if breaker is 1 that means syntax error, if breaker 0 that means it follow CFG
    if (breaker == 1) {
      cout << "Syntax Error! Your Input Didn't Follow the CFG! Expected i=i+i;" << endl;
    } else {
      cout << "Syntax Analyzing Successful! Your Input Follows the CFG" << endl;
    }
    break;

  }

  return 0;
}