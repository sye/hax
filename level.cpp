#include<stdio.h>
#include<stdlib.h>
#include "level.h"
#include "area.h"
#include "character.h"
/*#include<algorithm>
  #include<functional>*/

hax::Level::Level(){
    curChar = NULL;
    std::pair<std::string,CharOp*> go("go", new CharOpBool1String(&Character::go));
    charOps.push_back(go);
    opmap.insert(go);
    opmap["help"] = new LevelOpVoid(&Level::help);
    opmap["info"] = new LevelOpVoid(&Level::info);
    opmap["focus"] = new LevelOpBool1String(&Level::focus);
    opmap["spawn"] = new LevelOpVoid(&Level::spawn);
    opmap["kill"] = new LevelOpBool1String(&Level::kill);
    opmap["rest"] = new CharOpVoid(&Character::rest);

    ophelp["help"] = "Show a list of available commands";
    ophelp["info"] = "Show current status of this level";
    ophelp["focus <character>"] = "Select a character to perform actions";
    ophelp["spawn"] = "Spawn a random character";
    ophelp["kill <character>"] = "Kill a character";
    ophelp["go <route>"] = "Go to another area";
    ophelp["rest"] = "Rest to regain HP, MP and stamina";
}
hax::Level::Level(int n){
    Area* alist[] = {}; //fill with indoor and outdoor objects
    for(int i=0; i<n; i++){
        vec_area.push_back(alist[i]);
    }
}
/*hax::Level::Level(const Level& le){
  }*/
hax::Level::~Level(){
    std::cout<<"~Level: deleting name..."<<std::endl;
//    std::for_each(vec_area.begin(), vec_area.end(), std::mem_fun(&Level::delete));
    for(size_t i=0; i<vec_area.size(); i++){
        delete vec_area[i];
    }
    std::cout<<"name deleted"<<std::endl;
}

void hax::Level::add(Area* ar){
    vec_area.push_back(ar);
}
void hax::Level::add(Character* ch){
//    vec_char.push_back(ch);
    std::pair< std::map<std::string,Character*>::iterator, bool > ret;
    ret = players.insert( std::pair<std::string,Character*>(ch->getName(),ch) ); //will automatically check for key collisions
    if(ret.second == false){
        std::cout << "Character with name " << ret.first->second->getName() << " already exists" << std::endl; //TODO add appendix to name instead?
        delete ch;
    }
}
void hax::Level::action(){
    char const* vec_action[] = {"go","fight"};
}
void hax::Level::action(std::vector<std::string> words){
    const int num = words.size();
    Character* myChar;
    std::string op = "";
    int wordsRead = 0;
    if(num>0 && opmap.find(words[0]) != opmap.end()){
        myChar = curChar;
        op = words[0];
        wordsRead = 1;
    }else if(num>1 && opmap.find(words[0]+words[1]) != opmap.end() ){
        myChar = curChar;
        op = words[0]+words[1];
        wordsRead = 2;
    }else if(num>1 && players.find(words[0]) != players.end() && opmap.find(words[1]) != opmap.end()){
        myChar = players[words[0]];
        op = words[1];
        wordsRead = 2;
    }else if(num>2 && players.find(words[0]) != players.end() && opmap.find(words[1]+words[2]) != opmap.end()){
        myChar = players[words[0]];
        op = words[1]+words[2];
        wordsRead = 3;
    }else{
        std::cout << "Unknown command" << std::endl;
    }

    if(opmap.find(op) != opmap.end()){
        if(myChar != NULL){
            std::cout << "Character: " << myChar->getName() << std::endl;
        }
        std::cout << "Command: " << op << std::endl;
	std::cout << "wordsRead: " << wordsRead << " num: " << num << std::endl;
        std::vector<std::string> args;
        for(int i=wordsRead; i<num; i++){
            args.push_back(words[i]);
        }
	for(int i=0; i<args.size(); i++){
	    std::cout << args[i] << std::endl;
	}
        opmap[op]->call(args, myChar, this);
    }
}
bool hax::Level::focus(std::string selectChar){
    if(players.find(selectChar) != players.end()){
        curChar = players[selectChar];
        return true;
    }else{
        std::cout << "This character does not exist" << std::endl;
        return false;
    }
}
void hax::Level::info(){
    std::cout << "Total number of areas: " << vec_area.size() << std::endl;
    std::cout << "Total number of characters: " << players.size() << std::endl;
    std::string tmp;
    tmp.append("Current players: ");
    std::map<std::string, Character*>::const_iterator it;
    for(it = players.begin(); it != players.end(); it++){
        tmp.append(it->second->getName() + " in " + it->second->curArea->getName() + ", ");
    }
    std::cout << tmp << std::endl;
}
void hax::Level::help(){
    std::map<std::string,std::string>::iterator it = ophelp.begin();
    while(it != ophelp.end()){
        std::cout << it->first << " - " << it->second << std::endl;
        it++;
    }
}
void hax::Level::spawn(){
//TODO get random pointer from vec_area
    Area* spawnLocation = vec_area[0];
    Character* spawnedPlayer = spawnLocation->spawn();
    if(spawnedPlayer != NULL){
        add(spawnedPlayer);
    }
}
bool hax::Level::kill(std::string name){
    if(players.find(name) != players.end()){
        if(curChar != NULL && curChar->getName() == name){
            curChar = NULL;
        }
        Character* killedPlayer = players.find(name)->second;
        players.erase(name);
        delete killedPlayer;
        return true;
    }else{
        std::cout << "This character does not exist!" << std::endl;
        return false;
    }
}
