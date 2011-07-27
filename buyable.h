class Buyable{
public:
    void setPrice(int price){this->price = price;};
    int getPrice() const{return price;};
protected:
    int price;
};
