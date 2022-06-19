#include "server.hpp"

int main(){
    server test;
    sf::Thread p1(&server::addUser,&test);
    sf::Thread p2(&server::processTcp,&test);
    sf::Thread p3(&server::processUdp,&test);
    p1.launch();
    p2.launch();
    std::cout<<test.uSocket.getLocalPort()<<std::endl;
    p3.launch();
    return 0;
}