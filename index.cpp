#include <bits/stdc++.h> 
#include<math.h>
using namespace std;

struct product
{
  string line;
  string name;
  int qty;
  string cost;
  bool isImported = false;
  bool isExempted = false;
  string excemptType;
};

struct billDetails
{
  double cost;
  double tax;
};


int containsExcemptItems(string inputLine, vector<string> exemptItems){
  int index = -1;
  for(int i = 0; i < exemptItems.size(); i++){
    if(inputLine.find(exemptItems[i]) != string::npos) return i;
  }
  return index;
}

bool isImportedItem(string inputLine){
  if(inputLine.find("import") != string::npos) return true;
  return false;
}

string getCost(string inputLine){
  istringstream ss(inputLine);
 
    string word; // for storing each word
 
    // Traverse through all words
    // while loop till we get 
    // strings to store in string word
    while (ss >> word) {}
    
    return word;
}

string getLine(string inputLine, string cost){
  string s = "at " + cost;
    
    string::size_type i = inputLine.find(s);

    if (i != std::string::npos)
      inputLine.erase(i, s.length());
    return inputLine;
}

product preprocess(string inputLine){
  product item = product();

  item.line = inputLine;

  vector<string> exemptItems = {"book","chocolate","pills"};
  int exepmtItemIndex = containsExcemptItems(inputLine, exemptItems);
  if(exepmtItemIndex != -1){
    item.isExempted = true;
    item.excemptType = exemptItems[exepmtItemIndex];
  }

  item.isImported = isImportedItem(inputLine);
  item.cost = getCost(inputLine);
  item.line = getLine(inputLine, item.cost);
  item.qty = inputLine[0];

  return item;
}

vector<product> input(){
  vector<product> products;
  string inputLine;
  cout << endl << "Please enter input here. Enter '0' to end taking input" << endl;
  while(1){
    getline(cin, inputLine);
    if(inputLine[0] == '0') break;
    products.push_back(preprocess(inputLine));
  }
  return products;
}

double round(double var) 
{ 
    // 37.66666 * 100 =3766.66 
    // 3766.66 + .5 =3767.16    for rounding off value 
    // then type cast to int so value is 3767 
    // then divided by 100 so the value converted into 37.67 
    double value = (int)(var * 100 + .5); 
    return (double)value / 100; 
} 

billDetails getFinalBill(vector<product> &products){
  double totalCost = 0;
  double totalTax = 0;
  for(int i = 0; i < products.size(); i++){
    double cost = stod(products[i].cost), tax, tempTax = 0;
    if(!products[i].isExempted){
      tax = (cost * 0.1);
      tax = ceil(tax * 20) / 20;
      totalTax += tax;
      tempTax = tax;
    }
    if(products[i].isImported){
      tax = (cost * 0.05);
      tax = ceil(tax * 20) / 20;
      totalTax += tax;
      tempTax += tax;
    }
    tempTax += cost;
    totalCost += tempTax;
    if(tempTax > 0.0) products[i].line = products[i].line + ": " + to_string(tempTax).erase(5, 4);
  }
  totalTax = round(totalTax);
  billDetails finalBill = billDetails();
  finalBill.cost = totalCost;
  finalBill.tax = totalTax;
  return finalBill;
}

void printOutput(vector<product> products, billDetails finalbill){
  cout << "OUTPUT:" << endl;
  cout << "---------------------" << endl;
  for(int i = 0; i < products.size(); i++){
    cout << products[i].line << endl;
  }
  cout << "---------------------" << endl;
  cout << "Sales Taxes: " << finalbill.tax << endl;
  cout << "Total: " << finalbill.cost << endl;
}


int main() {
	vector<product> products = input();       // Takes input as list of items
  billDetails finalbill = getFinalBill(products);
  printOutput(products, finalbill);
}