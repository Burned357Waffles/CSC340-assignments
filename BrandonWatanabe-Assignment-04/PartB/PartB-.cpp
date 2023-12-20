#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

class Food {
public:
  Food(int count) : count(count) {}
  Food(string food)
  {
    name.reset(&food);
  }
  Food(string food, vector<string> ingredients)
  {
    name.reset(&food);
    ingredientsList.reset(&ingredients);
  }

private:
  int count = 0;
  unique_ptr<string> name{ nullptr };
  shared_ptr<vector<string>> ingredientsList{ nullptr };
};

//question 1 example  
void question1()
{
  Food* foodPtr1 = new Food(1);
  Food* foodPtr2 = foodPtr1;

  delete foodPtr1;
  foodPtr1 = nullptr;
  //delete foodPtr2;  Access Violation Exception
}


//question 2 example
void question2()
{
  unique_ptr<Food> Rice{ make_unique<Food>("rice") };
} // object is deleted and uPtr is set to nullptr


//question 3 example
void question3()
{
 /auto MacAndCheese{ make_unique<Food>("Macaroni & Cheese", vector<string> {"White cheddar cheese", "Cream", "Unsalted butter", "Salt", "Cayenne pepper", "Mace", "Dried breadcrumbs"}) };
} // the member variables are automatically deleted with the object

//question 4 example
void question4()
{
  auto Strawberry{ make_unique<Food>("strawberry") };
  //shared_ptr<Food> SharedStrawberry = move(Strawberry); // the object is now owned by a shared pointer instead of a unique pointer
}

//question 5 example
void question5()
{
  shared_ptr<Food> Fish{ make_shared<Food>("salmon") };
  weak_ptr<Food> weakFish{ Fish };
  weakFish.expired(); // will return false
  weakFish.reset();
  weakFish.expired(); // will return true
}

int main()
{
  question1();
  question2();
  question3();
  question4();
  question5();
}