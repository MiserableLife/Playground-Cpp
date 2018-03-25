/*
 *	move is one of the most important features in C++11 
 *	it removes unnecessary copy and creation. That leads to performance improvement
 *
 *
 * */


#include <iostream>
#include <ctime>


class Object
{
public:
	virtual const Object& operator=(const Object& obj){return *this;};
	virtual ~Object(){}
};
class HeavyObject : public Object
{
private:
	char str[100][10000];

public:
	HeavyObject()
	{
		for(int i=0; i< 100; i++)
			str[i][0]=0;
	}
	void copy(const Object& obj)
	{
		HeavyObject& ho = (HeavyObject&)obj;
		for(int i=0; i<100; i++)
			strcpy(str[i], ho.str[i]);

	}
	virtual const Object& operator=(const Object& obj)
	{
		copy(obj);
		return *this;
	}
	HeavyObject operator+(HeavyObject& ho)
	{
		HeavyObject result;
		result.copy(*this);
		for(int i=0; i<100; i++)
			strcat(result.str[i], ho.str[i]);
		return result;
	}
	~HeavyObject(){}
};

class LightObject : public Object 
{
private:
	int vals[100][10000];

public:
	void copy(const Object& obj)
	{
		LightObject& lo = (LightObject&)obj;
		memcpy(vals , lo.vals, sizeof(vals));
	}
	virtual const Object& operator=(const Object& obj)
	{
		copy(obj);
		return *this;
	}
	LightObject operator+(LightObject& lo)
	{
		LightObject result;
		result.copy(*this);
		for(int i=0; i<100; i++)
			for(int j=0; j<10000;j++)
				result.vals[i][j] += lo.vals[i][j];
		return result;
	}
	~LightObject(){}
};

template<typename T>
class MyCollector
{
protected:
	int capacity;
	int size;
	T ** obj_array;
public:
	MyCollector(int cap) : capacity(cap), size(0) 
	{
		obj_array = new T*[cap];
	}
	void insert(const T& obj)
	{
		insert(const_cast<T&>(obj));
	}

	void insert(T& obj)
	{
		if(size>=capacity)
			return;
		obj_array[size] = new T;
		*obj_array[size++] = obj; //copy to internal object
	}
	~MyCollector()
	{
		for(int i=0; i< size; i++)
			delete obj_array[i];
		delete[] obj_array;
	}


};

template<typename T>
class MyMoveCollector 
{
public:
	int capacity;
	int size;
	T ** obj_array;
public:
	MyMoveCollector(int cap) : capacity(cap), size(0) 
	{
		obj_array = new T*[cap];
	}
	void insert(const T& obj)
	{
		insert(const_cast<T&>(obj));
	}

	void insert(T& obj)
	{
		if(size>=capacity)
			return;
		obj_array[size] = new T;
		*obj_array[size++] = obj; //copy to internal object
	}
	void insert(T&& obj)
	{
		obj_array[size] = new T;
		*obj_array[size++] = obj;
	}	
	~MyMoveCollector()
	{
		for(int i=0; i< size; i++)
			delete obj_array[i];
		delete[] obj_array;
	}


};

void createAndInsertHeavy(MyCollector<HeavyObject>& coll)
{
	HeavyObject x;
	coll.insert(x);
	coll.insert(x+x);
	coll.insert(x);
}
void createAndInsertHeavy_move(MyMoveCollector<HeavyObject>& coll)
{
	HeavyObject x;
	coll.insert(x);
	coll.insert(x+x);
	coll.insert(std::move(x));
	
}
void createAndInsertLight(MyCollector<LightObject>& coll)
{
	LightObject x;
	coll.insert(x);
	coll.insert(x+x);
	coll.insert(x);
}
void createAndInsertLight_move(MyMoveCollector<LightObject>& coll)
{
	LightObject x;
	coll.insert(x);
	coll.insert(x+x);
	coll.insert(std::move(x));

}


int main()
{



	/* collection insert a new object. insert method makes an internal copy of the object passed by insert function  */
	/* to avoid inefficient call-by-value which calls copy-constructor, C++11 provides refernece declaration  */

/*	
	void createAndInsert(std::set& coll)
	{
		X x; 
		coll.insert(x); // inserts copy of x 
		... 
		coll.insert(x+x); // inserts copy of temporary rvalue 
		... 
		coll.insert(x); // inserts copy of x (although x is not used any longer)
	}
*/
	/* we create a local object x by costing a lot of resource. 
	 * we have to make a copy of x at the first insertion, because x will be used 
	 * we received a temporary rvalue which operator+ function makes and returns. at the second insertion, we pay another copy-cost because rvalue will be destroyed.. if we just move rvalue into collection? 
	 * we make a copy of x at the third insertion. we pay another copy-cost because after function, local variable will be destroyed... if we just move the object into collection?  */

	/* 결국 move 라는 것은 값 뿐만 아니라 생명주기도 가져가버리는 것을 의미함. y 가 의미하던 객체를 x 가 move 로 받는 경우 그 실체를 x가 가리키며 아예 x 가 원본이 되어버리는 개념.*/

	/* it makes great performance improvement when the copy cost of x is expensive ( if x has a lot of string)*/

	/* C++11 provides move. when using it, you have to specify that the temporary object is not used anymore */
	
	MyCollector<HeavyObject> coll(100);
	MyMoveCollector<HeavyObject> movecoll(100);
	clock_t begin = clock(); 
	
	createAndInsertHeavy(coll);

	clock_t end = clock();
	double elapsed_secs = double(end-begin)/CLOCKS_PER_SEC;
	std::cout<<"createAndInsertHeavy(lvalue reference version) takes "<<elapsed_secs<<" sec.."<<std::endl;

	begin = clock();

	createAndInsertHeavy_move(movecoll);

	end  = clock();

	elapsed_secs = double(end-begin)/CLOCKS_PER_SEC;
	std::cout<<"createAndInsertHeavy(rvalue refernece version) takes "<<elapsed_secs<<" sec.."<<std::endl;
	
	MyCollector<LightObject> lcoll(100);
	MyMoveCollector<LightObject> lmovecoll(100);
	begin = clock(); 
	
	createAndInsertLight(lcoll);

	end = clock();
	elapsed_secs = double(end-begin)/CLOCKS_PER_SEC;
	std::cout<<"createAndInsertLight(lvalue reference version) takes "<<elapsed_secs<<" sec.."<<std::endl;

	begin = clock();

	createAndInsertLight_move(lmovecoll);

	end  = clock();
 
	elapsed_secs = double(end-begin)/CLOCKS_PER_SEC;
	std::cout<<"createAndInsertLight(rvalue refernece version) takes "<<elapsed_secs<<" sec.."<<std::endl;
	


	/*
	X x; 
	coll.insert(x); // x의 복사본을 넣음. (x는 뒤에서 사용될거기 때문에) 
	... 
	coll.insert(x+x); // temporary rvalue (x+x의 결과) 내용을 옮겨옴
	...
	coll.insert(std::move(x)); // x의 내용을 std::move 로 옮겨옴.
*/
	/* std::move only converts the object into ravlue reference. rvalue reference type is  expressed as X&&  
	 * so we have to implement overload function for X&& */
/*
namespace std { 
template  class set { 
public: 
... 
insert (const T& x); // for lvalues: copies the value 
... 
insert (T&& x); // for rvalues: moves the value 
... 
};
}


move 의 source 에 해당되는 객체는 destination 에 영향을 줄만한 것들을 모두 제거해주어야함. 예를 들면 포인터 같은 것이 있음. 문자열을 내부적으로 갖는 객체는 move 를 하고 난 뒤 source
 와 destination 이 동시에 같은 지점을 가리킬 수 있음.  따라서 source 에서 조작이 가능할 수
 있기 때문에 clear 를 해주어야함. 그러나 실제로는 standard library 에서 알아서 clearing ( nullptr 넣기) 를 해주기 때문에 그럴 필요가 없다고 함. move 가 끝나고 나면 그 객체는 valid 하지만 unspecified 상태가 됨. 


마지막으로 중요한 두 가지 feature 가 존재함. 

* overloading rules for rvalues and lvalue reference 

rvalue 와 lvalue 에 대한 오버로딩은 다음과 같이 동작함. 

오로지 lvalue 만 구현한 경우 : void foo(X& );

C++98 과 같이 동작함. lvalue 에 대해서 호출되지만 rvalue 에 대해서는 호출되지 않음. 

const lvalue 만 구현한 경우 : void foo(const X& );
마찬가지로 C++98 과 같이 동작함. rvalue 와 lvalue 에 대해서 호출됨. 

lvalue 와 rvalue 모두 구현했거나 const lvalue 와 const rvalue 를 모두 구현한 경우 : 
rvalue 와 lvalue 처리하는 거에 대한 차이를 볼 수 있음. rvalue 용은 move semantic 사용가능함. 그래서 internal state 와 resource 를 그대로 가져올 수 있음. 

foo(X&&) 는 구현했는데 foo(X&) 와 foo(const X&) 모두 구현 안한경우 : 
foo() 는 rvalue 용으로 호출될 수 있지만 lvalue 에 대해서 호출하려는 게 존재하면 compile 에러 발생시킴. 그래서 move semantics 만이 사용될 수 있음. 이 테크닉에 대해서 더 알고자 한다면 unique pointers, file streams, string streams 들을 살펴보도록. 


* returning rvalue reference 

보통 어떤 값이나 객체를 리턴하는 경우 다음과 같이 많이 작성한다. 


X foo () { 
X x; 
return x;
} 

이 경우 다음의 동작들이 보장됨. 

X 가 copy 나 move 생성자를 가지고 있으면 compiler 는 copy 를 생략하도록 할 수 있음. 이게 소위 return value optimization  ((N)RVO) 이라 불리는 것임. C++11 이전에도 있어서 대부분의 컴파일러들에서 지원하던 개념. 

그게 아니고 move 생성자만 가지고 있으면 x는 move 됨. 

그것도 아니고 X가 copy 생성자만 가지고 있으면 x는 copy됨. 

그것도 아니면 compile time error 가 발생함. 

뿐만 아니라 rvalue refenrence 자체를 리턴하는 것은 에러라는걸 알아둬야함. 

아래와 같이 만약 반환되는 객체가 local 에 static object 가 아닌 경우를 보자. 


X&& foo () { 
X x; 
... 
return x; // ERROR returns reference to nonexisting object
} 

rvalue reference 는 말 그대로 reference 임. local object 에 대한 참조를 반환한다는 것은 
결국 더이상 존재하지 않는 객체에 대한 참조를 반환하는 것임. 따라서 std::move 가 사용되느냐는 아무런 상관이 없음. 




*/

	return 0;
}
