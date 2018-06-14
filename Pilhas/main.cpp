#include<iostream>
#include<stack>
#include<string>

using namespace std;

float operar(float a, float b, char operador)
{
    switch(operador)
    {
    case '+':
        return a+b;
    case '-':
        return a-b;
    case '*':
        return a*b;
    case'/':
        return a/b;
    default:
        cout<<"Erro, operador nao identificado";
        return 0;
    }
}

int prioridade(char operador)
{
    if(operador == '(')
        return 0;
    if(operador == '+'||operador == '-')
        return 1;
    return 2;
}

void resolverExpressao()
{
    stack<float> numeros;
    stack<char> operadores;
    string expressao;
    cin>>expressao;

    for(int i = 0; expressao[i]!='\0'; i++)
    {
        char atual = expressao[i];
        if(atual >= '0' && atual <='9')
        {
            float num = atual - '0';
            numeros.push(num);
        }
        else if(atual == '(')
        {
            operadores.push(atual);
        }
        else if(atual == '+' || atual == '-' || atual == '*' || atual=='/')
        {
            if(operadores.empty())
            {
                operadores.push(atual);
            }
            else
            {
                //Operar todos os operadores de prioridade superior ao que quero colocar na lista
                while(!operadores.empty() && prioridade(atual) <= prioridade(operadores.top()))
                {
                    float num2 = numeros.top();
                    numeros.pop();
                    float num1 = numeros.top();
                    numeros.pop();
                    char operador = operadores.top();
                    operadores.pop();
                    numeros.push(operar(num1,num2,operador));
                }
                operadores.push(atual);
            }
        }
        else if(atual == ')')   //Devo operar tudo que está entre parênteses quando for fechar
        {
            while(operadores.top()!='(')
            {
                float num2 = numeros.top();
                numeros.pop();
                float num1 = numeros.top();
                numeros.pop();
                char operador = operadores.top();
                operadores.pop();
                numeros.push(operar(num1,num2,operador));
            }
            operadores.pop();
        }
    }

    //Processar operadores restantes (desempilhando, de trás para frente)
    while(!operadores.empty())
    {
        float num2 = numeros.top();
        numeros.pop();
        float num1 = numeros.top();
        numeros.pop();
        char operador = operadores.top();
        operadores.pop();
        numeros.push(operar(num1,num2,operador));
    }

    cout<<numeros.top()<<endl;
}

int main()
{
    int numExpressoes;
    cin>>numExpressoes;
    for(int i = 0; i<numExpressoes; i++)
        resolverExpressao();
    return 0;
}
