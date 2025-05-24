#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>

class Account {
	protected:
		double balance;
	
	public:
		Account(double);
		virtual ~Account();

		virtual void deposit(double);
		virtual bool withdraw(double);
		double getBalance() const;

		//Operator overloading
		bool operator==(const Account&) const;
		bool operator!=(const Account&) const;

		//Friend function for output stream overload
		friend std::ostream& operator <<(std::ostream&, const Account&);

};

#endif  //ACCOUNT_H


