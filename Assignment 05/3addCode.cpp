#include <iostream>
#include<string>
#include <stack>
#include<vector>
using namespace std;
// defines the Boolean function for operator, operand, equalOrhigher precedence and the string conversion function.
bool IsOperator(char);
bool IsOperand(char);
bool eqlOrhigher(char, char);
string convert(string);
void threeAddCode(string,char);

int main()
{
    string infix_expression, postfix_expression;
    vector<string> threeAdd_expression;
    int ch;

    cout << " Enter an infix expression: ";
    cin >> infix_expression;
    

    //infix_expression = "k=a+b-c*d";
    char firstLetter=infix_expression[0];
    infix_expression=infix_expression.substr(2,infix_expression.length());

    postfix_expression = convert(infix_expression);
    cout << "\n Your Infix expression is: " << infix_expression<<endl;
    cout << "\n Postfix expression is: " << postfix_expression<<endl;

    threeAddCode(postfix_expression,firstLetter);


    return 0;
}

bool IsOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        return true;
    return false;
}

bool IsOperand(char c)
{
    if (c >= 'A' && c <= 'Z') /* Define the character in between A to Z. If not, it returns False.*/
        return true;
    if (c >= 'a' && c <= 'z') // Define the character in between a to z. If not, it returns False. */
        return true;
    if (c >= '0' && c <= '9') // Define the character in between 0 to 9. If not, it returns False. */
        return true;
    return false;
}
// define the precedence to the operator.
int precedence(char op)
{
    if (op == '+' || op == '-') /* it defines the lowest precedence */
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^') /* exponent operator has the highest precedence */ 
        return 3;       
return 0; 
} 
/* The eqlOrhigher() function is used to check the higher or equal precedence of the two operators in infix expression.  */
        bool eqlOrhigher(char op1, char op2)
        {
            int p1 = precedence(op1);
            int p2 = precedence(op2);
            if (p1 == p2)
            {
                if (op1 == '^')
                    return false;
                return true;
            }
            return (p1 > p2 ? true : false);
        }

    /* string convert() function is used to convert the infix expression to the postfix expression of the Stack */
    string convert(string infix)
    {
        stack<char> S;
        string postfix = "";
        char ch;

        S.push('(');
        infix += ')';

        for (int i = 0; i < infix.length(); i++)
        {
            ch = infix[i];

            if (ch == ' ')
                continue;
            else if (ch == '(')
                S.push(ch);
            else if (IsOperand(ch))
                postfix += ch;
            else if (IsOperator(ch))
            {
                while (!S.empty() && eqlOrhigher(S.top(), ch))
                {
                    postfix += S.top();
                    S.pop();
                }
                S.push(ch);
            }
            else if (ch == ')')
            {
                while (!S.empty() && S.top() != '(')
                {
                    postfix += S.top();
                    S.pop();
                }
                S.pop();
            }
        }
        return postfix;
    }


void threeAddCode(string pos,char firstChar)
{
    vector<string> exp_stack;
    int t=1;

    for(char i: pos){
        
        if(IsOperator(i)==false)
        {
            std::string s(1, i);
            exp_stack.push_back(s);
        }
        else
        {
            string tempT="t"+to_string(t);
            string temp=tempT+"="+exp_stack[exp_stack.size()-2]+i+exp_stack[exp_stack.size()-1];
            cout<<temp<<endl;
            exp_stack.pop_back();
            exp_stack.pop_back();
            exp_stack.push_back(tempT);
            t++;

        }
    }

    cout<<firstChar<<"="<<exp_stack[0];

    

}
