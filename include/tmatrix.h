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
  TDynamicVector(size_t size) : sz(size) {
    if (sz <= 0) {
      throw length_error("Vector size should be greater than zero");
    }
    if (sz > MAX_VECTOR_SIZE) {
      throw length_error("Vector size should not be greater than MAX_VECTOR_SIZE");
    }
    
    pMem = new T[sz]();

    return *this;
  }

  TDynamicVector(T* arr, size_t size) : sz(size) {
    if (arr == nullptr) {
      throw invalid_argument("The arr pointer must not be equal to nullptr");
    }
    
    pMem = new T[sz];
    for (size_t i = 0; i < sz; ++i) {
      pMem[i] = arr[i];
    }

    return *this;
  }

  TDynamicVector(const TDynamicVector& v) {
    this->sz = v.sz;

    pMem = new T[sz];
    for (size_t i = 0; i < sz; ++i) {
      pMem[i] = v.pMem[i];
    }
    
    return *this;
  }

  TDynamicVector(TDynamicVector&& v) noexcept {
    this->sz = v.sz;
    v.sz = 0;

    this->pMem = std::move(v.pMem);
    v.pMem = nullptr;

    return *this;
  }

  ~TDynamicVector() {
    delete[] pMem;
  }

  TDynamicVector& operator=(const TDynamicVector& v) {
    this->sz = v.sz;
    
    T* tempMem = new T[sz];
    for (size_t i = 0; i < sz; ++i) {
      tempMem[i] = v.pMem[i];
    }

    delete[] pMem;
    pMem = tempMem;

    return *this;
  }

  TDynamicVector& operator=(TDynamicVector&& v) noexcept {
    this->sz = v.sz;
    v.sz = 0;
    
    T* tempMem = std::move(v.pMem);
    v.pMem = nullptr;

    delete[] this-> pMem;
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
      throw out_of_range(Invalid index);
    }
    return this->pMem[index];
  }

  const T& at(size_t index) const {
    if (index < 0 || index >= sz) {
      throw out_of_range(Invalid index);
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
  TDynamicVector operator+(T value) {
    TDynamicVector<T> result(sz);
    for (size_t i = 0; i < tsz; ++i) {
      result[i] = this->pMem[i] + val;
    }
    return result;
  }

  TDynamicVector operator-(T value) {
    TDynamicVector<T> result(sz);
    for (size_t i = 0; i < sz; ++i) {
      result[i] = this->pMem[i] - val;
    }
    return result;
  }

  TDynamicVector operator*(T value) {
    TDynamicVector<T> result(sz);
    for (size_t i = 0; i < sz; ++i) {
      result[i] = this->pMem[i] * val;
    }
    return result;
  }

  // Векторные операции
  TDynamicVector operator+(const TDynamicVector& v) {
    if (this->sz != v.sz) {
      throw logic_error("The size of the vectors must match");
    }
    
    TDynamicVector<T> result(sz);
    for (size_t i = 0; i < sz; ++i) {
      result[i] = this->pMem[i] + v.pMem[i];
    }
    return result;
  }

  TDynamicVector operator-(const TDynamicVector& v) {
    if (this->sz != v.sz) {
      throw logic_error("The size of the vectors must match");
    }
    
    TDynamicVector<T> result(sz);
    for (size_t i = 0; i < sz; ++i) {
      result[i] = this->pMem[i] - v.pMem[i];
    }
    return result;
  }

  T operator*(const TDynamicVector& v) {

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

template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>> {
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;

public:
  TDynamicMatrix(size_t size) : TDynamicVector<TDynamicVector<T>>(size) {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // Cравнение
  bool operator==(const TDynamicMatrix& m) const noexcept {
  
  }

  // Матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val) {
  
  }

  // Матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v) {
  
  }

  // Матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m) {
  
  }

  TDynamicMatrix operator-(const TDynamicMatrix& m) {
    
  }

  TDynamicMatrix operator*(const TDynamicMatrix& m) {
    
  }

  // Ввод/Вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v) {
    
  }

  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v) {
    
  }
};

#endif
