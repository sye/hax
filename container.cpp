#include "container.h"

hax::Container::Container(){
}
/*hax::Container::Container(const Container& co) : Object(co){
  vec_obj = co.vec_obj;
  }*/
hax::Container::~Container(){
    std::cout << "~Container: emptying " << description() << "..." << std::endl;
    for(size_t i=0; i<vec_obj.size(); i++){
        delete vec_obj[i];
    }
    vec_obj.clear();
}

hax::Object* hax::Container::operator[](size_t i){ //TODO const version?
    return vec_obj[i];
}

bool hax::Container::add(Object* ob){
    if(weight+ob->getWeight() > hold_weight() || volume+ob->getVolume() > hold_volume()){
        return false;
    }else{
        vec_obj.push_back(ob);
        weight += ob->getWeight();
        volume += ob->getVolume();
        price += ob->getPrice();
        return true;
    }
}
bool hax::Container::remove(Object* ob){
    if( findObject(ob) != vec_obj.end() ){
        vec_obj.erase(findObject(ob));
        weight -= ob->getWeight();
        volume -= ob->getVolume();
        price -= ob->getPrice();
        return true;
    }else{
        return false;
    }
}
size_t hax::Container::size() const{
    return vec_obj.size();
}
hax::Object* hax::Container::pop(){ //TODO not used
    Object* lastObj = vec_obj.back();
    vec_obj.pop_back();
    return lastObj;
}
bool hax::Container::empty() const{
    return vec_obj.empty();
}
std::vector<hax::Object*>::iterator hax::Container::findObject(Object* ob){
    std::vector<Object*>::iterator it;
    for(it = vec_obj.begin(); it != vec_obj.end(); it++){
        if(*it == ob){
            return it;
        }
    }
    return it; //not found, return vec_obj.end()
}
std::vector<hax::Object*>::iterator hax::Container::findObject(std::string objName){
    std::vector<Object*>::iterator it;
    for(it = vec_obj.begin(); it != vec_obj.end(); it++){
        if((*it)->description() == objName){
            return it;
        }
    }
    return it; //not found, return vec_obj.end()
}
bool hax::Container::hasObject(Object* ob){
    std::vector<Object*>::iterator it;
    for(it = vec_obj.begin(); it != vec_obj.end(); it++){
        if(*it == ob){
            return true;
        }
    }
    return false;
}


hax::Wallet::Wallet(){
    name = "wallet";
    weight = 1;
    volume = 1;
    price = 0;
/*
  const char* attr[] = { //attributes
  "shiny",
  "Hello Kitty",
  "old"
  };
*/
    descr = "old";
//    descr = attr[random int]; TODO

}
hax::Wallet* hax::Wallet::operator+=(const int profit){ //add Coins equal to int value
    *this -= (-profit);
    return this;
}
hax::Wallet* hax::Wallet::operator-=(const int cost){ //TODO return NULL first if cost > this->getPrice() ???
//pop coins until have enough then create new Coins for växel
    int payment = 0;
    while(payment < cost){
        Object* mynt = vec_obj.front(); //TODO change to Coin* when implement template
        this->remove(mynt);
        payment += mynt->getPrice();
        delete mynt; //give to shopkeeper, gone forever
    }
    int change = payment - cost;
/*            for(int i=0; i<change; i++){
              this->add(new CuCoin());
              }
*/
//          Coin moneyValue[] = {CuCoin(), FeCoin(), NiCoin()}; //TODO get sizeof and use in while loop
    std::vector<Coin> moneyValue;
    moneyValue.push_back(CuCoin());
    moneyValue.push_back(FeCoin());
    moneyValue.push_back(NiCoin());
//          int i=0;
//          while(moneyValue[i] != NULL){ //TODO safe to do this?
    for(size_t i=0; i<moneyValue.size(); i++){
        int numCoin = change / moneyValue[i].getPrice(); //truncated division
        change -= numCoin * moneyValue[i].getPrice();
        for(int j=0; j<numCoin; j++){
            this->add(new Coin(moneyValue[i]));
        }
//              i++;
    }
/*          int numAuCoin = change/10;
            int leftover = change - numAuCoin*10;
            int numAgCoin = change/5;
            leftover = change - numAgCoin*5;
            int numCuCoin = leftover;
*/
    return this;
}
int hax::Wallet::hold_weight() const{
    return 1;
}
int hax::Wallet::hold_volume() const{
    return 1000;
}

hax::Pocket::Pocket(){
    name = "pocket";
    descr = "nobody's";
}
hax::Pocket::Pocket(std::string owner, unsigned int maxSize){
    name = "pocket";
    descr = owner +"'s";
    weight = 1;
    volume = 1;
    this->maxSize = maxSize;
}
int hax::Pocket::hold_weight() const{ //TODO hold_size() instead
    return 100;
}
int hax::Pocket::hold_volume() const{
    return 100;
}

hax::Ground::Ground(std::string areaName){
    name = "ground";
//          weight = -1;
//          volume = -1;
    descr = areaName;
}
int hax::Ground::hold_weight() const{
    return 10000;
}
int hax::Ground::hold_volume() const{
    return 10000;
}
