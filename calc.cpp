#include "calc.h"
#include "./ui_calc.h"
#include "BigNum.h"
#include <string>
#include <queue>
#include <stack>

using std::queue;
using std::stack;
using std::string;

class QueEle
{
    enum Type
    {
        Num,
        Op
    };
    Type type;
    BigNum num;
    char op;

public:
    QueEle(bool option, const string &S)
    {
        type = option ? Op : Num;
        if (type == Op)
            op = S[0];
        else
            num = BigNum(S);
    }
    void print() const
    {
        if (type == Op)
            cout << op;
        else
            num.print();
    }
    bool is_num() const
    {
        return type == Num;
    }
    BigNum GetNum() const
    {
        return num;
    }
    char GetOp() const
    {
        return op;
    }
};

Calc::Calc(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calc)
{
    ui->setupUi(this);
    this->setWindowTitle("Calculator");
    this->setFixedSize(282, 317);

    ui->textOutput->setPlainText("0");
    ui->beq->setFixedSize(QSize(60, 65));
}

Calc::~Calc()
{
    delete ui;
}

void Calc::on_bpls_clicked()
{
    Input += "+";
    ui->textInput->setPlainText(Input);
}


void Calc::on_bsub_clicked()
{
    Input += "-";
    ui->textInput->setPlainText(Input);
}


void Calc::on_btime_clicked()
{
    Input += "*";
    ui->textInput->setPlainText(Input);
}


void Calc::on_bdiv_clicked()
{
    Input += "/";
    ui->textInput->setPlainText(Input);
}


void Calc::on_b7_clicked()
{
    Input += "7";
    ui->textInput->setPlainText(Input);
}


void Calc::on_b8_clicked()
{
    Input += "8";
    ui->textInput->setPlainText(Input);
}


void Calc::on_b9_clicked()
{
    Input += "9";
    ui->textInput->setPlainText(Input);
}


void Calc::on_bl_clicked()
{
    Input += "(";
    ui->textInput->setPlainText(Input);
}


void Calc::on_b4_clicked()
{
    Input += "4";
    ui->textInput->setPlainText(Input);
}


void Calc::on_b5_clicked()
{
    Input += "5";
    ui->textInput->setPlainText(Input);
}


void Calc::on_b6_clicked()
{
    Input += "6";
    ui->textInput->setPlainText(Input);
}


void Calc::on_br_clicked()
{
    Input += ")";
    ui->textInput->setPlainText(Input);
}

void Calc::on_b1_clicked()
{
    Input += "1";
    ui->textInput->setPlainText(Input);
}

void Calc::on_b2_clicked()
{
    Input += "2";
    ui->textInput->setPlainText(Input);
}


void Calc::on_b3_clicked()
{
    Input += "3";
    ui->textInput->setPlainText(Input);
}

void Calc::Invalid_Input()
{
    ui->textOutput->setPlainText("Invalid Input!");
}

void Calc::on_b0_clicked()
{
    Input += "0";
    ui->textInput->setPlainText(Input);
}




void Calc::on_beq_clicked()
{
    // Input
    const string s = Input.toStdString() + " ";

    // Convert infix to suffix
    queue<QueEle> Q;
    stack<char> Sta;
    const int len = s.length();
    bool is_num = 0;
    string tmp_num = "";
    for (int i = 0; i < len; i++)
    {
        if ('0' <= s[i] && s[i] <= '9')
        {
            is_num = 1;
            tmp_num += s[i];
            continue;
        }
        else if (is_num)
        {
            is_num = 0;
            Q.push(QueEle(0, tmp_num));
            tmp_num = "";
        }
        if (s[i] == '*' || s[i] == '/')
        {
            while (!Sta.empty() && (Sta.top() == '*' || Sta.top() == '/'))
            {
                Q.push(QueEle(1, string(1, Sta.top())));
                Sta.pop();
            }
            Sta.push(s[i]);
        }
        else if (s[i] == '+' || s[i] == '-')
        {
            while (!Sta.empty() && (Sta.top() == '*' || Sta.top() == '/' || Sta.top() == '+' || Sta.top() == '-'))
            {
                Q.push(QueEle(1, string(1, Sta.top())));
                Sta.pop();
            }
            Sta.push(s[i]);
        }
        else if (s[i] == '(')
            Sta.push(s[i]);
        else if (s[i] == ')')
        {
            while (!Sta.empty() && (Sta.top() != '('))
            {
                Q.push(QueEle(1, string(1, Sta.top())));
                Sta.pop();
            }
            Sta.pop();
        }
    }
    while (!Sta.empty())
    {
        Q.push(QueEle(1, string(1, Sta.top())));
        Sta.pop();
    }

    // Calc
    stack<BigNum> sta;
    while (!Q.empty())
    {
        const QueEle now = Q.front();
        Q.pop();
        if (now.is_num())
            sta.push(now.GetNum());
        else
        {
            if (sta.size() < 2)
            {
                Invalid_Input();
                return;
            }
            const BigNum B = sta.top();
            sta.pop();
            const BigNum A = sta.top();
            sta.pop();
            switch (now.GetOp())
            {
            case '+':
                sta.push(A + B);
                break;
            case '-':
                sta.push(A - B);
                break;
            case '*':
                sta.push(A * B);
                break;
            case '/':
                sta.push(A / B);
                break;
            }
        }
    }

    // Output
    if (sta.size() != 1)
        Invalid_Input();
    else
    {
        Output = QString::fromStdString(sta.top().printString());
        ui->textOutput->setPlainText(Output);
    }
}

void Calc::on_bdel_clicked()
{
    Input.removeLast();
    ui->textInput->setPlainText(Input);
}


void Calc::on_bc_clicked()
{
    Input.clear();
    ui->textInput->setPlainText(Input);
}

