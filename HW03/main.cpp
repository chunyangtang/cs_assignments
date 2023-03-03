//
//  main.cpp
//  FloatingPointsTool
//
//  Created by 范静涛 on 2023/3/1.
//

#include <iostream>
#include <type_traits>

struct SingleFloat{
    unsigned int Fraction  : 23;
    unsigned int Exponent  : 8;
    unsigned int IsNagtive : 1;
};

struct DoubleFloat{
    unsigned long long Fraction  : 52;
    unsigned long long Exponent  : 11;
    unsigned long long IsNagtive : 1;
};

template <typename FloatType>
union FloatingPointsTool {
    //to limit FloatType in {double, float}
    using F_Type = typename std::enable_if<std::is_same<double, FloatType>::value || std::is_same<float, FloatType>::value, FloatType>::type;
    using U_Type = typename std::conditional_t<std::is_same<double, FloatType>::value, unsigned long long, unsigned int>;
    using S_Type = typename std::conditional_t<std::is_same<double, FloatType>::value, DoubleFloat, SingleFloat>;
    //constructors
    explicit FloatingPointsTool(F_Type Value);
    explicit FloatingPointsTool(U_Type Value);
    //Getter
    bool IsDenormalized() const;
    bool IsNormalized() const;
    bool IsInfinite() const;
    bool IsNaN() const;
    bool IsNagtive() const;
    bool IsZero() const;
    F_Type GetFltValue() const;
    U_Type GetUIntValue() const;
    //Setter
    void SetIsNagive(bool Value);
    void SetExponent(unsigned int Value);
    void SetFraction(unsigned long long Value);
private:
    F_Type FValue;
    U_Type UValue;
    S_Type Components;
};

template <typename FloatType>
FloatingPointsTool<FloatType>::FloatingPointsTool(F_Type Value){
    FValue = Value;
}

template <typename FloatType>
FloatingPointsTool<FloatType>::FloatingPointsTool(U_Type Value){
    UValue = Value;
}

template <typename FloatType>
bool FloatingPointsTool<FloatType>::IsDenormalized() const{
    // insert code here...
}

template <typename FloatType>
bool FloatingPointsTool<FloatType>::IsNormalized() const{
    // insert code here...
}

template <typename FloatType>
bool FloatingPointsTool<FloatType>::IsInfinite() const{
    // insert code here...
}

template <typename FloatType>
bool FloatingPointsTool<FloatType>::IsNaN() const{
    // insert code here...
}

template <typename FloatType>
bool FloatingPointsTool<FloatType>::IsNagtive() const{
    // insert code here...
}

template <typename FloatType>
bool FloatingPointsTool<FloatType>::IsZero() const{
    // insert code here...
}

template <typename FloatType>
typename FloatingPointsTool<FloatType>::F_Type FloatingPointsTool<FloatType>::GetFltValue() const{
    // insert code here...
}

template <typename FloatType>
typename FloatingPointsTool<FloatType>::U_Type FloatingPointsTool<FloatType>::GetUIntValue() const{
    // insert code here...
}

template <typename FloatType>
void FloatingPointsTool<FloatType>::SetIsNagive(bool Value){
    // insert code here...
    Components.IsNagtive = Value;
}

template <typename FloatType>
void FloatingPointsTool<FloatType>::SetExponent(unsigned int Value) {
    // insert code here...
}

template <typename FloatType>
void FloatingPointsTool<FloatType>::SetFraction(unsigned long long Value) {
    // insert code here...
}

int main(int argc, const char * argv[]) {
    //Demo By fan
    FloatingPointsTool<double> f1(1ULL);
    f1.SetExponent(0xFFFFFFFF);
    f1.SetFraction(0x1);
    
    // insert code here...
    
    std::cout << "Floating Point Value: " << f1.GetFltValue() << std::endl;
    std::cout << "Unsigned Integer Value: " << std::hex << f1.GetUIntValue() << std::endl;
    std::cout << "IsDenormalized: " << f1.IsDenormalized() << std::endl;
    std::cout << "IsNormalized: " << f1.IsNormalized() << std::endl;
    std::cout << "IsInfinite: " << f1.IsInfinite() << std::endl;
    std::cout << "IsNaN: " << f1.IsNaN() << std::endl;
    std::cout << "IsZero: " << f1.IsZero() << std::endl;
    std::cout << "IsNagtive: " << f1.IsNagtive() << std::endl;
    return 0;
}
