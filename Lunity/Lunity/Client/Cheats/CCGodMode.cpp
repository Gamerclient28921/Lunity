#include "pch.h"
#include "CCGodMode.h"
//#include "Speed.h"
//#include "../Hooks/KeyHook.h"
#include "../../SDK/EntList.h"

//float spyeet = 0.2f;
float aaabbb = 4.0f;

CCGodMode::CCGodMode() : Cheat::Cheat("CCGodMode", "Other")
{
}

Vector2 RunAngles;

void CCGodMode::onPacket(void* Packet, PacketType type, bool* cancel)
{
	if (enabled) {
		if (type == PacketType::Movement) {
			/*		if (type == PacketType::Movement) {
						MovePlayerPacket* pkt = (MovePlayerPacket*)Packet;
						pkt->Pos.y += 8;
						//Vector3 myPosition = *LunMem::getClientInstance()->LocalPlayer->getPos();
						//pkt->Pos.x = myPosition.x;
						//pkt->Pos.z = myPosition.z; //to fix the lagbacks, doesnt work
					}
				}
			*/
			RakNetInstance* Raknet = LunMem::getClientInstance()->LoopbackPacketSender->NetworkHandler->RakNetInstance;
			LocalPlayer* player = LunMem::getClientInstance()->LocalPlayer;
			vector<Actor*>* ents = getEntities();
			for (uint i = 0; i < ents->size(); i++) {
				if (LunMath::distanceVec3(*ents->at(i)->getPos(), *player->getPos()) <= 3.5f) {
					//do stuff
					MovePlayerPacket* pkt = (MovePlayerPacket*)Packet;
					pkt->Pos.y += aaabbb;
					aaabbb -= 0.001f;
					RunAngles = LunMath::getRotationAnglesToEnt(*ents->at(i)->getPos(), *player->getPos());
					//Logger::log(to_string(RunAngles.x));
					//Logger::log(to_string(RunAngles.y));
					//player->VelocityXYZ.x = -0.3f * (cos((RunAngles.y + 90.0f) * (3.14 / 180.0f)));
					//player->VelocityXYZ.z = -0.3f * (sin((RunAngles.y + 90.0f) * (3.14 / 180.0f)));

					pkt->Pos.x += -2.0f * (cos((RunAngles.y + 90.0f) * (3.14 / 180.0f)));
					pkt->Pos.z += -2.0f * (sin((RunAngles.y + 90.0f) * (3.14 / 180.0f)));
				}
				else
				{
					aaabbb = 4.0f;
				}
			}
		}
	}
}

void CCGodMode::onTick()
{
	Cheat::onTick();
	//cuz of lagbacks but doesnt fix it work Dx
	/*	if (LunMem::getClientInstance() != NULL) {
			if (LunMem::getClientInstance()->LocalPlayer != NULL) {
				LocalPlayer* Player = LunMem::getClientInstance()->LocalPlayer;
				float calcYeet = Player->LookingVec.y;

				if (KeyHook::KeyState(0x57)) {
					if (!KeyHook::KeyState(0x41) && !KeyHook::KeyState(0x44)) {
						calcYeet += 90.0f;
					}
					else if (KeyHook::KeyState(0x41)) {
						calcYeet += 45.0f;
					}
					else if (KeyHook::KeyState(0x44)) {
						calcYeet += 135.0f;
					}
				}
				else if (KeyHook::KeyState(0x53)) {
					if (!KeyHook::KeyState(0x41) && !KeyHook::KeyState(0x44)) {
						calcYeet -= 90.0f;
					}
					else if (KeyHook::KeyState(0x41)) {
						calcYeet -= 45.0f;
					}
					else if (KeyHook::KeyState(0x44)) {
						calcYeet -= 135.0f;
					}
				}
				else if (!KeyHook::KeyState(0x57) && !KeyHook::KeyState(0x53)) {
					if (KeyHook::KeyState(0x44)) {
						calcYeet += 180.0f;
					}
				}

				if (KeyHook::KeyState(0x57) | KeyHook::KeyState(0x53) | KeyHook::KeyState(0x41) | KeyHook::KeyState(0x44)) {
					Player->VelocityXYZ.x = cos((calcYeet) * (3.14f / 180.0f)) * spyeet;
					Player->VelocityXYZ.z = sin((calcYeet) * (3.14f / 180.0f)) * spyeet;
				}
			}
		}
	*/
}