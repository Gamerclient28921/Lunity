#include "pch.h"
#include "GlideBoost.h"

#define PI 3.14159

float glideBoostSpeed = 1.2;
bool moving = false;
Vector3* savedPos;
Vector2 lookingVec;

GlideBoost::GlideBoost() :Cheat::Cheat("GlideBoost", "Movement")
{

}

void GlideBoost::onEnable()
{
	Cheat::onEnable();
}

void GlideBoost::onDisable()
{
	Cheat::onDisable();
}

void GlideBoost::onPacket(void* Packet, PacketType type, bool* cancel) {
	if (moving) {
		if (strcmp(rak->ServerIp.getText(), "geo.hivebedrock.network") == 0) {

		}
		if (type == Movement) {
			MovePlayerPacket* pkt = (MovePlayerPacket*)Packet;
			pkt->Pos.x = 0;
			pkt->Pos.y = 0;
			pkt->Pos.z = 0;
		}
	}
}

Vector3 Nofavec;
void GlideBoost::onTick()
{
	Cheat::onTick();
	if (LunMem::getClientInstance() != NULL) {
		if (LunMem::getClientInstance()->LocalPlayer != NULL) {
			RakNetInstance* rak = LunMem::getClientInstance()->LoopbackPacketSender->NetworkHandler->RakNetInstance;
			LocalPlayer* Player = LunMem::getClientInstance()->LocalPlayer;
			if (KeyHook::KeyState(0x47)) {
				if (!moving) {
					savedPos = Player->getPos();
					lookingVec = Player->LookingVec;
					Logger::log("Moving!");
					moving = true;
				}
				if (moving) {

					LunMem::Nop((BYTE*)LunMem::getBaseModule() + 0x900617, 3);

					Player->VelocityXYZ.x = cos((Player->LookingVec.y + 90) * (PI / 180.0f)) * glideBoostSpeed;
					Player->VelocityXYZ.y = (float)0;
					Player->VelocityXYZ.z = sin((Player->LookingVec.y + 90) * (PI / 180.0f)) * glideBoostSpeed;

					if (strcmp(rak->ServerIp.getText(), "mco.cubecraft.net") == 0) {
						//Lucy's disabler (outdated, same as flare those scumbags)
						Vector3* posa = Player->getPos();
						Vector3* bedPos = new Vector3{ posa->x, posa->y - 1.6f, posa->z };
						Vector3* pos = Player->getPos();
						Nofavec = *pos;
						Nofavec.y += 1.6;
						MovePlayerPacket* a = new MovePlayerPacket((Actor*)Player, &Nofavec, &Player->LookingVec, 0x0);
						LunMem::getClientInstance()->LoopbackPacketSender->sendToServer(a);
						delete a;
						Nofavec.y -= 1.6;
						MovePlayerPacket* a2 = new MovePlayerPacket((Actor*)Player, &Nofavec, &Player->LookingVec, 0x0);
						LunMem::getClientInstance()->LoopbackPacketSender->sendToServer(a2);
						delete a2;
					}
					
				}
			}
			else {
				if (moving) {
					LunMem::Patch((BYTE*)LunMem::getBaseModule() + 0x900617, (BYTE*)"\xFF\x50\x08", 3);
					moving = false;
					Player->VelocityXYZ.x = (float)0;
					Player->VelocityXYZ.y = (float)0;
					Player->VelocityXYZ.z = (float)0;
					Logger::log("No Longer Moving!");
				}
			}
		}
	}
}