/*================================================================
*   
*   文件名称：calculator.cpp
*   创 建 者：baozhenhua(鲍振华)
*   创建日期：2018年09月13日
*   描    述：
*
================================================================*/


#include<iostream>
#include<sstream>
#include<string>
#include<regex>
#include"Stack"

class EItem{
	public:
		int num;
		char priority;
	public:
		EItem(){}
		EItem(int num,char priority=0){
			this->num=num;
			this->priority=priority;
		}
		EItem* find(char ch){
			if((int)ch==num) return this;
			return NULL;
		}
};
EItem charItem[10];	
int calc(std::string exp){
	//if(!std::regex_match(exp,std::regex("(-?\\d+)(\\ *[+\\-*/]\\ *-?\\d+)*"))) throw 3;
	Stack<EItem> expressions;
	Stack<EItem> c;

	std::istringstream inexp(exp);
	int sum=0;
	while(inexp.peek()!=EOF){
		char ch=inexp.get();
		if(ch>='0' && ch<='9'){
			sum=sum*10+(int)ch-48;
		}
		else{
			EItem e(sum);
			expressions.push(e);
			for(int i=0;i<4;i++){
				EItem* ec=charItem[i].find(ch);
				if(ec!=NULL){
					if(c.empty()){
						c.push(*ec);
						break;
					}
					int size=c.size();
					for(int j=0;j<size;j++){

						if(ec->priority>c.top().priority){
							c.push(*ec);
							break;
						}
						else{
							EItem temp=c.top();
							expressions.push(temp);
							c.pop();
							if(c.empty()){
								c.push(*ec);
								break;
							}
						}
					}
					break;
				}
			}
			
			sum=0;
		}
	}
	EItem e(sum);
	expressions.push(e);
	while(!c.empty()){
		expressions.push(c.top());
		c.pop();
	
	}

	int q=0;
	EItem* result=new EItem[200];
	while(!expressions.empty()){		
		result[q]=expressions.top();
		expressions.pop();
		q++;
	}
	for(int i=q-1;i>=0;i--){
		if(result[i].priority==0){
			expressions.push(result[i]);
		}
		else{
			int b=expressions.top().num;
			expressions.pop();
			int a=expressions.top().num;
			expressions.pop();
			switch((char)result[i].num){
				case '+':
					expressions.push(a+b);
					break;
				case '-':
					expressions.push(a-b);
					break;
				case '*':
					expressions.push((int)(a*b));
					break;
				case '/':
					expressions.push((int)(a/b));
					break;

			}
		}
	}
	return expressions.top().num;
}
int main(){
	charItem[0].num='+';
	charItem[0].priority=20;
	charItem[1].num='-';
	charItem[1].priority=20;		
	charItem[2].num='*';
	charItem[2].priority=30;
	charItem[3].num='/';
	charItem[3].priority=30;
	std::string exp;
	std::cin>>exp;
	std::cout<<calc(exp)<<std::endl;
    
    
    
    
    return 0;
}
