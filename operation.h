#ifndef OPERATION_H
#define OPERATION_H

#include<vector>
#include<cstring>
#include<exception>

namespace hax{

    //check if function initlized by: if(function > 0)
   
    typedef std::vector<std::string> Arguments;

    class OperationVoid{
    private:
        typedef void(*Function)(void);
        Function function;
    public:
        void virtual operator()(const Arguments args) const{ //TODO change to this where it's used (nicer code)
            call(args);
        };
        virtual void call(const Arguments args) const{
            if(!args.empty()){
                throw std::exception();
            }
            (*function)();
        };

        OperationVoid(){
        };
        OperationVoid(Function function){ //will not be inherited
            this->function = function;    
        };
    };
//REMEMBER can't inherit from templated-class
//REMEMBER can't have templates with different arg-count but same name :(
    
    class OperationVoid1String : public OperationVoid{
    private: //TODO should these Function function be protected instead??
        typedef void(*Function)(std::string);
        Function function;
    public:
        virtual void call(const Arguments args) const{
            if(args.size()!=1){
                throw std::exception();
            }
            (*function)(args[0]);
            return;
        };
        OperationVoid1String(Function function){
            this->function = function;  
        };
    };

     class OperationVoid2String : public OperationVoid{
    private: //TODO should these Function function be protected instead??
        typedef void(*Function)(std::string,std::string);
        Function function;
    public:
        virtual void call(const Arguments args) const{
            if(args.size()!=2){
                throw std::exception();
            }
            (*function)(args[0],args[1]);
            return;
        };
        OperationVoid2String(Function function){
            this->function = function; 
        };
    };

    
    template <typename T>
    class Operation1Arg : public OperationVoid{
    private:    
        typedef void(*Function)(T);
        Function function;
    protected:
        typedef std::map<std::string,T>* Domain0;
        Domain0 domain0; //using a pointer to the domain it can be updated;ex add/rem a new player
    public:
        virtual void call(const Arguments args) const{
            if(args.size()!=1 || domain0->find(args[0])==domain0->end()){ //check number of args and the domain for each arg
                throw std::exception();
            }
            (*function)((*domain0)[args[0]]); //call
            return;
        };
    
        Operation1Arg(Function function,Domain0 domain0){
            this->function = function;
            this->domain0 = domain0;
        };
    };

    template <typename T>
    class Operation1Arg1String : public OperationVoid{
    private: //TODO should these Function function be protected instead??
        typedef void(*Function)(T,std::string);
        Function function;
    protected:
        typedef std::map<std::string,T>* Domain0;
        Domain0 domain0; //using a pointer to the domain it can be updated;ex add/rem a new player

    public:
        virtual void call(const Arguments args) const{
            if(args.size()!=2||domain0->find(args[0])==domain0->end()){
                throw std::exception();
            }
            (*function)( (*domain0)[args[0]] , args[1] );
            return;
        };
        Operation1Arg1String(Function function){
            this->function = function; 
        };
    };

    template <typename T,typename U>
    class Operation2Arg : public OperationVoid {//inherites to code for T
    private:
        typedef void(*Function)(T,U);
        Function function;
    protected:
        typedef std::map<std::string,T>* Domain0;
        Domain0 domain0;
        typedef std::map<std::string,U>* Domain1;
        Domain1 domain1;
    public:
        virtual void call(const Arguments args) const{
            if(args.size()!=2 || domain0->find(args[0])==domain0->end() || domain1->find(args[1])==domain1->end()){
                throw std::exception();    
            }
            (*function)(domain0[args[0]],domain1[args[1]]);
            return;
        };

        Operation2Arg( Function function,Domain0 domain0,Domain1 domain1){
            this->function = function;
            this->domain0 = domain0;
            this->domain1 = domain1;
        };
    };

    template<typename M>
    class MemberOperationVoid : public OperationVoid{
    private:
        typedef void(M::*Function)(void);
        Function function;
    protected:
        typedef std::map<std::string,M*>* DomainM;
        DomainM domainM;
    public:
        virtual void call(const Arguments args) const{
            if(args.size()!=1 || domainM->find(args[0])==domainM->end()){
                throw std::exception();
            };
            ((*domainM)[args[0]]->*function)();
            return;
        };
        MemberOperationVoid( Function function,DomainM domainM){
            this->function = function;
            this->domainM = domainM;
        };

    };

    template<typename M>
    class MemberOperationVoid1String : public OperationVoid{
    private:
        typedef void(M::*Function)(std::string);
        Function function;
    protected:
        typedef std::map<std::string,M*>* DomainM;
        DomainM domainM;
    public:
        virtual void call(const Arguments args) const{
            if(args.size()!=2 || domainM->find(args[0])==domainM->end()){
                throw std::exception();
            };
            ((*domainM)[args[0]]->*function)(args[1]);
            return;
        };
        MemberOperationVoid1String( Function function,DomainM domainM){
            this->function = function;
            this->domainM = domainM;
        };

    };

    template<typename M,typename T>
    class MemberOperation1Arg : public OperationVoid{ 
    private:
        typedef void(M::*Function)(T);
        Function function;
    protected:
        typedef std::map<std::string,M*>* DomainM;
        DomainM domainM;
        typedef std::map<std::string,T>* Domain0;
        Domain0 domain0;
    public:
        virtual void call(const Arguments args) const{
            if(args.size()!=2||domainM->find(args[0])==domainM->end()||domain0->find(args[1])==domain0->end()){
                throw std::exception();
            };
            ((*domainM)[args[0]]->*function)((*domain0)[args[1]]);
            return;
        };
        MemberOperation1Arg( Function function,DomainM domainM,Domain0 domain0){
            this->function = function;
            this->domainM = domainM;
            this->domain0 = domain0;
        };

    };

}

#endif
