#include <BigInt/BigInt.h>

#include <iostream>
#include <vector>

using namespace std;

namespace ACA
{

BigInt::BigInt(const string& s)
{
	if(s[0] == '0' && s.length()!=1){
		throw std::invalid_argument("the argument must not start with 0");
	}
	for(char ch : s){
		if(!std::isdigit(ch)){
			throw std::invalid_argument("the argument must consist only digits");
		}
	}

	digits = s; 
}

BigInt::BigInt(unsigned long long nr)
{
	digits = to_string(nr);
}

BigInt::BigInt(const BigInt& other)
{
	digits = other.digits;
}

BigInt& BigInt::operator=(const BigInt& other)
{
    // Guard self assignment
    if (this != &other)
    {
        digits = other.digits;
    }
    return *this;
}


/*
BigInt& BigInt::operator=(BigInt other) noexcept
{
    // exchange resources between *this and other
    std::swap(digits, other.digits);
    return *this;
}
*/

bool operator==(const BigInt& lhs, const BigInt& rhs)
{
    return lhs.digits == rhs.digits;
}

bool operator!=(const BigInt& lhs, const BigInt& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const BigInt& lhs, const BigInt& rhs)
{
	if(lhs.digits.length() < rhs.digits.length()){
		return true;
	}
	if(lhs.digits.length() > rhs.digits.length()){
		return false;
	}
    for(int i = 0 ; i < lhs.digits.length(); i++){
		if(lhs.digits[i] < rhs.digits[i]){
			return true;
		}
		if(lhs.digits[i] > rhs.digits[i]){
			return false;
		}
	}
	return false;
}

bool operator>(const BigInt& lhs, const BigInt& rhs)
{
	return rhs < lhs;
}

bool operator>=(const BigInt& lhs, const BigInt& rhs)
{
	return !(lhs < rhs);
}

bool operator<=(const BigInt& lhs, const BigInt& rhs)
{
	return !(lhs > rhs);
}

BigInt& BigInt::operator++()
{
	for(int i = digits.length()-1; i >= 0; i--){
		if(digits[i] != '9'){
			digits[i] = (digits[i] - 47) + '0';
			break;
		}
		digits[i] = '0';
	}
	if(digits[0]=='0'){
		digits.insert(0,"1");
	}
    return *this;
}

BigInt BigInt::operator++(int /* tmp */)
{
	BigInt old = *this;
	operator++(); // prefix increment
	return old;
}

BigInt& BigInt::operator--()
{
	if(digits == "0"){
		throw std::out_of_range ("cannot decrement 0");
	}
	for(int i = digits.length()-1; i >= 0; i--){
		if(digits[i] != '0'){
			digits[i] = (digits[i] - 49) + '0';
			break;
		}
		digits[i] = '9';
	}
	if(digits[0]=='0' && digits.length()!=1){
		digits.erase(0, 1);
	}
    return *this;
}

BigInt BigInt::operator--(int /* tmp */)
{
	BigInt old = *this;
	operator--(); // prefix decrement
	return old;
}

BigInt& BigInt::operator+=(const BigInt& rhs)
{
	int a = 0;
	int length = std::min(digits.length(), rhs.digits.length());
	for(int i = 0; i < length; i++){
		if(digits[digits.length()-i-1] + rhs.digits[rhs.digits.length()-i-1] + a - 96 > 9){
			digits[digits.length()-i-1] = (digits[digits.length()-i-1] + rhs.digits[rhs.digits.length()-i-1] + a - 106) + '0';
			a = 1;
			continue;
		}
		digits[digits.length()-i-1] = (digits[digits.length()-i-1] + rhs.digits[rhs.digits.length()-i-1] + a - 96) + '0';
		a=0;
	}
	if(a==1){
		if(digits.length()==length){
			digits.insert(0,"1");
		}
		else{
			string tmp = digits;
			digits = digits.substr(0, digits.length()-length);
			++*this;
			digits.append(tmp.substr(tmp.length() - length, length));
		}
	}
	if(digits.length() < rhs.digits.length()){
		if(a==1){
			string tmp = digits;
			digits = rhs.digits.substr(0,rhs.digits.length() - length);
			++*this;
			digits.append(tmp.substr(1, tmp.length()));
		}
		else{
			digits.insert(0, rhs.digits.substr(0,rhs.digits.length() - length));
		}
	}
    return *this;
}

BigInt operator+(BigInt lhs, const BigInt& rhs)
{
	lhs += rhs;
	return lhs;
}

BigInt& BigInt::operator-=(const BigInt& rhs)
{
	if(*this < rhs){
		throw std::out_of_range ("cannot subtract bigger number");
	}
	int a = 0;
	for(int i = 0; i < rhs.digits.length(); i++){
		if(digits[digits.length()-i-1] - a - 48 < rhs.digits[rhs.digits.length()-i-1] - 48){
			digits[digits.length()-i-1] = (digits[digits.length()-i-1] - rhs.digits[rhs.digits.length()-i-1] - a + 10) + '0';
			a = 1;
			continue;
		}
		digits[digits.length()-i-1] = (digits[digits.length()-i-1] - rhs.digits[rhs.digits.length()-i-1] - a) + '0';
		a=0;
	}

	if(a == 1){
		string tmp = digits;
		digits = digits.substr(0,digits.length() - rhs.digits.length());
		--*this;
		digits.append(tmp.substr(tmp.length() - rhs.digits.length(), rhs.digits.length()));
	}

	int count = 0;
	for(int i = 0; i < digits.length()-1; i++){
		if(digits[i]!='0'){
			break;
		}
		count++;
	}
	digits = digits.substr(count, digits.length() - count);
    return *this;
}

BigInt operator-(BigInt lhs, const BigInt& rhs)
{
	lhs -= rhs;
	return lhs;
}

BigInt& BigInt::operator*=(const BigInt& rhs)
{
	// TODO
    return *this;
}

BigInt operator*(BigInt lhs, const BigInt& rhs)
{
	lhs *= rhs;
	return lhs;
}

BigInt& BigInt::operator/=(const BigInt& rhs)
{
	// TODO
    return *this;
}

BigInt operator/(BigInt lhs, const BigInt& rhs)
{
	lhs /= rhs;
	return lhs;
}

BigInt& BigInt::operator%=(const BigInt& rhs)
{
	// TODO
    return *this;
}

BigInt operator%(BigInt lhs, const BigInt& rhs)
{
	lhs %= rhs;
	return lhs;
}

BigInt& BigInt::operator^=(const BigInt& rhs)
{
	// TODO
    return *this;
}

BigInt operator^(BigInt lhs, const BigInt& rhs)
{
	lhs ^= rhs;
	return lhs;
}

istream& operator>>(istream& in, BigInt& a)
{
    // TODO
    return in;
}

ostream& operator<<(ostream& out, const BigInt& a)
{
	out << a.toString();
    return out;
}

} // namespace ACA