//
// Created by maj3 on 03.04.17.
//

#include <cstring>
#include "iostream"
#include "Matrix.h"
using namespace std;
namespace algebra {
    Matrix::Matrix() {}

    Matrix::Matrix(int r, int c) {
        row = r;
        col = c;
        mat = new complex<double> *[row];
        for (auto i = 0; i < row; i++) {
            mat[i] = new complex<double>[col];
        }
    }
    Matrix::Matrix(initializer_list<vector<complex<double>>> a){
        int r=0;
        for(auto n : a)
        {
            r++;
            int c=0;
            for(auto m : n)
            {
                c++;
            }
            col=c;
        }
        row=r;
        mat = new complex<double> *[row];
        for (auto i = 0; i < row; i++) {
            mat[i] = new complex<double>[col];
        }
        int i=0;
        for(auto n : a)
        {
            int j=0;
            for(auto m : n)
            {
                mat[i][j] = m;
                j++;
            }
            i++;
        }
    }



    Matrix::~Matrix() {
        for (auto i = 0; i < row; i++) {
            delete[] mat[i];
        }
        delete[] mat;
    }

    Matrix Matrix::Add(Matrix a) const {
        Matrix result;
        result.col = col;
        result.row = row;
        result.mat = new complex<double> *[row];
        for (auto i = 0; i < row; i++) {
            result.mat[i] = new complex<double>[col];
        }
        if (row == a.row && col == a.col) {
            for (auto i = 0; i < row; i++) {
                for (auto j = 0; j < col; j++) {

                    result.mat[i][j] = mat[i][j] + a.mat[i][j];
                }
            }

        }
        return result;
    }

    pair<size_t, size_t> Matrix::Size() {
        return {row, col};
    }

    Matrix Matrix::Sub(Matrix a) const{
        Matrix result;
        result.col = col;
        result.row = row;
        result.mat = new complex<double> *[row];
        for (auto i = 0; i < row; i++) {
            result.mat[i] = new complex<double>[col];
        }
        if (row == a.row && col == a.col) {
            for (auto i = 0; i < row; i++) {
                for (auto j = 0; j < col; j++) {
                    result.mat[i][j] = mat[i][j] - a.mat[i][j];
                }
            }

        }
        return result;
    }

    Matrix Matrix::Mul(Matrix a) const{
        Matrix result;
        if(a.row==col) {
            result.col = a.col;
            result.row = row;
            result.mat = new complex<double> *[row];
            for (auto i = 0; i < row; i++) {
                result.mat[i] = new complex<double>[a.col];
            }
            for (auto i = 0; i < row; i++) {
                for (auto j = 0; j < a.col; j++) {
                    complex<double> sum(0, 0);
                    for (auto k = 0; k < col; k++) {
                        sum += mat[i][k] * a.mat[k][j];
                    }
                    result.mat[i][j] = sum;
                }
            }
        }
        else
        {
            result.col=0;
            result.row=0;
            result.mat= nullptr;
        }
        return result;
    }

    Matrix Matrix::Div(Matrix a) {}

    Matrix Matrix::Pow(int a) {
        int k=1;
        Matrix result;
        if(row==col && a>=0) {
            result.col = col;
            result.row = row;
            result.mat = new complex<double> *[row];
            for (auto i = 0; i < row; i++) {
                result.mat[i] = new complex<double>[col];
            }
            for (auto i = 0; i < row; i++) {
                for (auto j = 0; j < col; j++)
                    result.mat[i][j] = mat[i][j];
            }
            if(a==1)
                return result;
            if(a>0)
            {
                while(k!=a) {
                    result = this->Mul(result);
                    k++;
                }
            }
            else
            {
                for (auto i = 0; i < row; i++) {
                    for (auto j = 0; j < col; j++) {
                        if (i == j && a==0) {
                            result.mat[i][j] = complex<double>(1, 0);
                        } else {
                            result.mat[i][j] = complex<double>(0, 0);
                        }
                    }
                }
            }
        }
        else
        {
            result.col=0;
            result.row=0;
            result.mat= nullptr;
        }
        return result;
    }

    string Matrix::Print() const {
        string temp = "[";
        string tt = "";
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                tt = to_string(mat[i][j].real());
                int s = tt.size() - 1;
                while (tt[s] == '0') {
                    tt.pop_back();
                    --s;
                    if (tt[s] == '.') {
                        tt.pop_back();
                        break;
                    }
                }
                temp += tt;
                temp += 'i';
                tt = to_string(mat[i][j].imag());
                s = tt.size() - 1;
                while (tt[s] == '0') {
                    tt.pop_back();
                    --s;
                    if (tt[s] == '.') {
                        tt.pop_back();
                        break;
                        }
                    }
                temp += tt;
                if(j%col==col-1 && i!=row-1) {
                    temp += ';';
                    temp += ' ';
                }
                else
                {
                    if(j!=col-1 || i!=row-1) {
                        temp += ',';
                        temp += ' ';
                    }
                }
                }

            }
        temp += ']';
        return temp;
    }

    Matrix::Matrix(const Matrix &a) {
        row = a.row;
        col = a.col;
        mat = new complex<double> *[a.row];
        for (auto i = 0; i < a.row; i++) {
            mat[i] = new complex<double>[a.col];
        }
        for (auto i = 0; i < a.row; i++) {
            for (auto j = 0; j < a.col; j++)
                mat[i][j] = a.mat[i][j];
        }
    }
    Matrix & Matrix::operator=(const Matrix& a) {
        if (this == &a) {
            return *this;
        }
        for (auto i = 0; i < row; i++) {
            delete[] mat[i];
        }
        delete[] mat;
        row=a.row;
        col=a.col;
        mat = new complex<double> *[a.row];
        for (auto i = 0; i < a.row; i++) {
            mat[i] = new complex<double>[a.col];
        }
        for (auto i = 0; i < a.row; i++) {
            for (auto j = 0; j < a.col; j++)
                mat[i][j] = a.mat[i][j];
        }
    }
    Matrix::Matrix(const char *a) {

        string cp;
        int siz = 1, counter = 0;
        col = 1;
        for (int i = 0; i < strlen(a); i++) {
            cp.push_back(a[i]);
            if (a[i] == ' ') {
                siz++;
                col++;
            }
            if (a[i] == ';')
                col = 0;
        }
        vector<complex<double>> tab;
        row = 1;

        for (int i = 0; i < cp.size(); i++) {
            int pos1;
            int pos2;
            double real = 0;
            double im = 0;
            if (cp[i] == '[')
                continue;
            else {
                if (isdigit(cp[i])) {
                    pos1 = i;
                    while (isdigit(cp[i + 1]) || cp[i + 1] == '.') {
                        i++;
                    }
                    pos2 = i;

                    const string &temp1 = cp.substr(pos1, pos2);
                    real = stod(temp1);
                    if (cp[i + 1] == 'i') {
                        i += 2;
                        pos1 = i;
                        while (isdigit(cp[i + 1]) || cp[i + 1] == '.') {
                            i++;
                        }
                        pos2 = i;
                        const string &temp2 = cp.substr(pos1, pos2);
                        im = stod(temp2);
                    }
                    tab.push_back(complex<double>(real, im));
                } else {
                    if (cp[i] == ' ' || cp[i] == ',')
                        continue;
                    else {
                        if (cp[i] == ';') {
                            row++;
                            continue;
                        } else
                            break;
                    }
                }
            }
        }

        int k = 0;
        mat = new complex<double> *[row];

        for (auto i = 0; i < row; i++) {
            mat[i] = new complex<double>[col];
        }
        for (auto i = 0; i < row; i++) {
            for (auto j = 0; j < col; j++) {
                mat[i][j] = tab[k];
                k++;
            }
        }
    }
}

