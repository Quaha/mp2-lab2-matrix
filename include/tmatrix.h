// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - шаблонный вектор на динамической памяти

template<typename T> class TDynamicVector {
protected:
    size_t sz = 0;
    T* pMem = nullptr;

public:

    TDynamicVector() {}

    TDynamicVector(size_t size) : sz(size) {
        if (sz < 0) {
            throw length_error("Vector size should be non negative");
        }
        if (sz > MAX_VECTOR_SIZE) {
            throw length_error("Vector size should not be greater than MAX_VECTOR_SIZE");
        }

        if (sz != 0) {
            pMem = new T[sz];
        }
    }

    TDynamicVector(T* arr, size_t size) : sz(size) {
        if (sz < 0) {
            throw length_error("Vector size should be non negative");
        }
        if (sz > MAX_VECTOR_SIZE) {
            throw length_error("Vector size should not be greater than MAX_VECTOR_SIZE");
        }

        if (sz > 0) {
            pMem = new T[sz];
            for (size_t i = 0; i < sz; ++i) {
                pMem[i] = arr[i];
            }
        }
    }

    TDynamicVector(const TDynamicVector& v) {
        this->sz = v.sz;

        if (sz > 0) {
            pMem = new T[sz];
            for (size_t i = 0; i < sz; ++i) {
                pMem[i] = v.pMem[i];
            }
        }
    }

    TDynamicVector(TDynamicVector&& v) noexcept {
        this->sz = v.sz;
        v.sz = 0;

        this->pMem = std::move(v.pMem);
        v.pMem = nullptr;
    }

    ~TDynamicVector() {
        delete[] pMem;
    }

    TDynamicVector& operator=(const TDynamicVector& v) {
        this->sz = v.sz;

        if (sz > 0) {
            T* tempMem = new T[sz];
            for (size_t i = 0; i < sz; ++i) {
                tempMem[i] = v.pMem[i];
            }

            delete[] pMem;
            pMem = tempMem;
        }
        else {
            delete[] pMem;
            pMem = nullptr;
        }

        return *this;
    }

    TDynamicVector& operator=(TDynamicVector&& v) noexcept {
        this->sz = v.sz;
        v.sz = 0;

        T* tempMem = std::move(v.pMem);
        v.pMem = nullptr;

        delete[] this->pMem;
        this->pMem = std::move(tempMem);

        return *this;
    }

    size_t size() const noexcept {
        return sz;
    }

    // Индексация
    T& operator[](size_t index) {
        return this->pMem[index];
    }

    const T& operator[](size_t index) const {
        return this->pMem[index];
    }

    // Индексация с контролем
    T& at(size_t index) {
        if (index < 0 || index >= sz) {
            throw out_of_range("Invalid index");
        }
        return this->pMem[index];
    }

    const T& at(size_t index) const {
        if (index < 0 || index >= sz) {
            throw out_of_range("Invalid index");
        }
        return this->pMem[index];
    }

    // Сравнение
    bool operator==(const TDynamicVector& v) const noexcept {
        if (this->sz != v.sz) {
            return false;
        }
        for (size_t i = 0; i < sz; ++i) {
            if (this->pMem[i] != v.pMem[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const TDynamicVector& v) const noexcept {
        if (this->sz != v.sz) {
            return true;
        }
        for (size_t i = 0; i < sz; ++i) {
            if (this->pMem[i] != v.pMem[i]) {
                return true;
            }
        }
        return false;
    }

    // Скалярные операции
    TDynamicVector operator+(const T &value) const {
        TDynamicVector<T> result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result[i] = this->pMem[i] + value;
        }
        return result;
    }

    TDynamicVector operator-(const T &value) const {
        TDynamicVector<T> result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result[i] = this->pMem[i] - value;
        }
        return result;
    }

    TDynamicVector operator*(const T &value) const {
        TDynamicVector<T> result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result[i] = this->pMem[i] * value;
        }
        return result;
    }

    // Векторные операции
    TDynamicVector operator+(const TDynamicVector& v) const{
        if (this->sz != v.sz) {
            throw logic_error("The size of the vectors must match");
        }

        TDynamicVector<T> result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result[i] = this->pMem[i] + v.pMem[i];
        }
        return result;
    }

    TDynamicVector operator-(const TDynamicVector& v) const {
        if (this->sz != v.sz) {
            throw logic_error("The size of the vectors must match");
        }

        TDynamicVector<T> result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result[i] = this->pMem[i] - v.pMem[i];
        }
        return result;
    }

    T operator*(const TDynamicVector& v) const {
        if (this->sz != v.sz) {
            throw logic_error("The size of the vectors must match");
        }

        if (!std::is_default_constructible<T>::value) {
            throw logic_error("Wrong template type");
        }

        T result = static_cast<T>(0);
        for (size_t i = 0; i < sz; ++i) {
            result += this->pMem[i] * v.pMem[i];
        }
        return result;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // Ввод/Вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v) {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v) {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - шаблонная матрица на динамической памяти

template<typename T> class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>> {
public:
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;

public:
    TDynamicMatrix(size_t size) : TDynamicVector<TDynamicVector<T>>(size) {
        if (sz < 0) {
            throw length_error("Matrix size should be non negative");
        }
        if (sz > MAX_MATRIX_SIZE) {
            throw length_error("Matrix size should not be greater than MAX_Matrix_SIZE");
        }

        for (size_t i = 0; i < sz; i++) {
            pMem[i] = TDynamicVector<T>(sz);
        }
    }

    TDynamicMatrix(size_t size, const T& elem) : TDynamicMatrix(size) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                pMem[i][j] = elem;
            }
        }
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    T& at(size_t i, size_t j) {
        if (i < 0 || i >= sz || j < 0 || j >= sz) {
            throw out_of_range("Invalid index");
        }
        return pMem[i][j];
    }

    const T& at(size_t i, size_t j) const {
        if (i < 0 || i >= sz || j < 0 || j >= sz) {
            throw out_of_range("Invalid index");
        }
        return pMem[i][j];
    }

    // Cравнение
    bool operator==(const TDynamicMatrix& m) const noexcept {
        if (this->sz != m.sz) return false;
        for (int i = 0; i < sz; i++) {
            if (this->pMem[i] != m.pMem[i]) {
                return false;
            }
        }
        return true;
    }

    // Матрично-скалярные операции
    TDynamicMatrix<T> operator*(const T& val) const {
        TDynamicMatrix<T> result(sz);
        for (int i = 0; i < sz; i++) {
            result[i] = pMem[i] * val;
        }
        return result;
    }

    // Матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v) const {
        if (this->sz != v.size()) {
            throw logic_error("The size of the vectors must match");
        }

        TDynamicVector<T> result(sz);
        for (int i = 0; i < sz; i++) {
            result[i] = this->pMem[i] * v;
        }

        return result;
    }

    // Матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m) const {
        if (this->sz != m.sz) {
            throw logic_error("The size of the matrix must match");
        }

        TDynamicMatrix<T> result(sz);
        for (int i = 0; i < sz; i++) {
            result[i] = this->pMem[i] + m.pMem[i];
        }

        return result;
    }

    TDynamicMatrix operator-(const TDynamicMatrix& m) const {
        if (this->sz != m.sz) {
            throw logic_error("The size of the matrix must match");
        }

        TDynamicMatrix<T> result(sz);
        for (int i = 0; i < sz; i++) {
            result[i] = this->pMem[i] - m.pMem[i];
        }

        return result;
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m) const {
        if (this->sz != m.sz) {
            throw logic_error("The size of the matrix must match");
        }

        TDynamicMatrix<T> result(sz);
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                result[i][j] = 0;
            }
        }

        for (int i = 0; i < sz; i++) {
            for (int k = 0; k < sz; k++) {
                for (int j = 0; j < sz; j++) {
                    result[i][j] += this->pMem[i][k] * m.pMem[k][j];
                }
            }
        }

        return result;
    }

    size_t size() const noexcept {
        return sz;
    }

    // Ввод/Вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& m) {
        
        for (int i = 0; i < m.sz; i++) {
            cin >> m.pMem[i];
        }

        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m) {
        
        for (int i = 0; i < m.sz; i++) {
            cout << m.pMem[i] << "\n";
        }

        return ostr;
    }
};

#endif
