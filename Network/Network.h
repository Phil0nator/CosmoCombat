//http://enet.bespin.org/Downloads.html //Networking protocal
#include "host.c"



enum EntityUpdateType{
    ENTITY_UPDATE_NONE, UPDATE_VECTOR, UPDATE_STATE
};

struct PacketMeta{

    int time;
    PacketMeta(){
        time = now();
    }

};

struct EntityServerEvent{
    
    PacketMeta meta;
    int ID;
    int dat[4]; //x,y,velx,vely

};

struct PlayerServerEvent{ 
    PacketMeta meta;
    int ID;
    int dat[4]; //x,y,velx,vely

};

struct ParticleServerEvent{

    PacketMeta meta;
    int x;
    int y;
    int amt;
    Particle_Type type;

};

//global variables:
ENetHost * client;
ENetAddress address;
ENetEvent event;
ENetPeer *peer;


void connectToServer(){
    
}
void connectToClient(){

}
void initializeNetworkServer(){

}

void initializeNetworkClient(){
    enet_initialize();
    client = enet_host_create (NULL /* create a client host */,
            1 /* only allow 1 outgoing connection */,
            2 /* allow up 2 channels to be used, 0 and 1 */,
            0 /* assume any amount of incoming bandwidth */,
            0 /* assume any amount of outgoing bandwidth */);

}

ENetPacket * PackEventType(void*ptr){

    

    ENetPacket * out = enet_packet_create(ptr,sizeof(ptr),ENET_PACKET_FLAG_RELIABLE);
    cout << out->data << endl;
    return out;

}

void unpack(ENetPacket* packet, void* dest){

    unsigned char *buffer = (char*) malloc(sizeof(packet));
    memcpy(&buffer,( const unsigned char* )packet, sizeof(packet));
    memcpy(dest, &buffer, sizeof(packet));

}




#include "Network.cpp"