#include <iostream>
#include <string>
#include "strutils.h"


using namespace std;


//end condition
bool termination(string s){
	
	if(s == "QUIT" || s =="exit" || s=="quit" || s=="EXIT" || s=="END" || s=="end")
		return false;
	else
		return true;

} 

//check if i'th position is number
bool isNumber(string s, int i){
	
	char  c= s.at(i);
	if(c == '1' || c == '2' ||  c == '3' || c == '4' || c == '5' ||  c == '6' ||
		 c == '7' || c == '8' || c == '9' ||  c == '0' || c == '.' ){
		
			return true;
	}
	else
		return false;

}

//check if i'th position is + or - or / or *
bool isAdd(string s , int i){
	char  c= s.at(i);
	if(c == 43) //bi bak ASCII kullanımına
		return true;
	else
		return false;
}
bool isSub(string s , int i){
	char  c= s.at(i);
	if(c == 45)
		return true;
	else
		return false;
}
bool isDiv(string s, int i){
	char  c= s.at(i);
	if(c == 47)
		return true;
	else
		return false;
}
bool isMult(string s, int i){
	char  c= s.at(i);
	if(c == 42)
		return true;
	else
		return false;
}


//check if there is any non-number or non-operator
bool invalidtype(string s){
	int length = s.length();
	int i=0, counter=0;
	
	while(i<length){
		if(isNumber(s,i))
			counter++;
		else if(isAdd(s,i))
			counter++;
		else if(isMult(s,i))
			counter++;
		else if(isSub(s,i))
			counter++;
		else if(isDiv(s,i))
			counter++;

		i++;
	}

	if(counter == length)
		return true;
	else
		return false;

}


//decide to whole opreator
int decider(string s){
	
	int i=0;
	while(isNumber(s,i)){
		i++;
		
		if(i >= s.length())
			return 0;
	}

	if(i < s.length())
		return i;
	else
		return 0;

}

//if no operands left it means calculation is over
bool movetosum(string s){
	

	if(s.find("+") == string::npos && s.find("-")==string::npos && s.find("/") == string::npos && s.find("*") == string::npos )
		return false;
	else
		return true;
	

}




int main(){
	string input="";
	
	int i=0;
	string numb=""; // sum == numleft + numright == numb
	double sum =0;
	string numl="", numr="";
	bool negative = false; //it becomes true when equation is negative
	
	
	
	while(true){
	
	cout<<"Please enter an expression to calculate:";
	cin>>input;

		if(!termination(input)){
		cout<<"GOOD BYE";
		return 0;
	}
	
		while(!invalidtype(input)){
		cout<<"Invalid input."<<endl<<endl;
		cout<<"Please enter an expression to calculate:";
		cin>>input;

		if(!termination(input)){
		cout<<"GOOD BYE";
		return 0;
	}
		
	}

	 negative = false;
	
	//CALCULATOR PART
	while(movetosum(input)){
		
		int length = input.length();

		if(isAdd(input , decider(input))){
			
			if(decider(input) == 0){
				cout<<"Invalid input"<<endl<<endl;
				break;
			}

			
			
			int addition =input.find("+");
			numl = input.substr(0,addition);
		
			int j=addition+1;
			while( j<length && isNumber(input,j) ){
				j++;
			}

			if(j == addition+1){
				cout<<"Invalid input."<<endl<<endl;
				break;
			}

			if(negative){
				numl = "-" + numl;
			}
			

			numr = input.substr(addition+1,j-(addition+1));
			sum = atof(numl) + atof(numr);
			numb = std::to_string(sum);
			input.replace(0,j,numb);

			if(sum<0){
			negative = true;
			input.erase(0,1);

		}else
			negative = false;

		}
		else if(isSub(input , decider(input)) ){
		
			if(decider(input) == 0){
				cout<<"Invalid input"<<endl<<endl;
				break;
			}
			
			double subtraction =input.find("-");
			numl = input.substr(0,subtraction);
			
			int j=subtraction+1;
			while(  j<length && isNumber(input,j)){
				j++;
			}

			if(j == subtraction+1){
			cout<<"Invalid input"<<endl<<endl;
				break;
			}
			
		
		numr= input.substr(subtraction+1,j-(subtraction+1));
		
		if(negative){
			numl = "-" + numl;
		}

		sum = atof(numl) - atof(numr);
		
		numb = std::to_string(sum);
		input.replace(0,j,numb);

		if(sum<0){
			negative = true;
			input.erase(0,1);

		}else
			negative = false;
		

	}
	else if(isDiv(input , decider(input))){
		
		if(decider(input) == 0){
				cout<<"Invalid input"<<endl<<endl;
				break;
			}
		
		double division =input.find("/");
		numl = input.substr(0,division);
		int j=division+1;
		
		while( j<length && isNumber(input,j) ){
		j++;
		}
		
		if(j == division+1){
		cout<<"Invalid input"<<endl<<endl;
				break;
		}
			
		
		numr= input.substr(division+1,j-(division +1));

		if(negative){
		numl = "-" + numl;
		}

		if(numr =="0"){
			cout<<"You cannot divide by 0."<<endl<<endl;
			break;
		}

		sum = atof(numl) / atof(numr);
		numb = std::to_string(sum);
		input.replace(0,j,numb);

	}
	else if(isMult(input , decider(input))){
		
		if(decider(input) == 0){
				cout<<"Invalid input"<<endl<<endl;
				break;
			}
		
		int multiplication =input.find("*");
		numl = input.substr(0,multiplication);
		
		int j=multiplication+1;
		while(  j<length && isNumber(input,j) ){
		j++;
		}
		
		if(j == multiplication+1){
		cout<<"Invalid input"<<endl<<endl;
		break;
		}
			
		
		numr= input.substr(multiplication+1,j-(multiplication+1));

		sum = atof(numl) * atof(numr);
		numb = std::to_string(sum);
		input.replace(0,j,numb);


	}
	

	}

	if(!movetosum(input)){
		
		if(negative){
		input = "-" + input;
		}
		sum = atof(input);
		cout << sum<<endl<<endl;
		sum=0;
	
	}

	
	sum=0;
	}
	

	cin.ignore();
	cin.get();
	return 0;
}