#include <ScriptObject.h>
#include <Territory/QuestBattle.h>
#include <Actor/Player.h>
#include <Actor/GameObject.h>
#include <Actor/BNpc.h>

using namespace Sapphire;

class LurkersintheGrotto : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_BOSS = 4083604;
  static constexpr auto INIT_POP_01_01 = 4083606;
  static constexpr auto INIT_POP_01_02 = 4083607;
  static constexpr auto INIT_POP_02_01 = 4083608;
  static constexpr auto INIT_POP_02_02 = 4083609;
  static constexpr auto INIT_POP_02_03 = 4083610;
  static constexpr auto INIT_POP_02_04 = 4083611;
  static constexpr auto INIT_P_POP_01 = 4083622;
  static constexpr auto CUT_SCENE_01 = 133;
  static constexpr auto HOW_TO_QIB = 79;
  static constexpr auto TEXT_YSHTOLA_BATTLETALK_01 = 82;

  enum Variables : uint8_t
  {
    SET_1_SPAWNED,
    SET_2_SPAWNED,
    SUCCESS_CALLED
  };

public:
  LurkersintheGrotto() : Sapphire::ScriptAPI::QuestBattleScript( 35 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "Blueflame", 2001709, 0, 4127684, 4, { 212.863602f, 76.055717f, -263.921509f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance", 2001710, 4127721, 4127718, 5, { 243.772705f, 76.571930f, -296.237213f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Blueflame_1", 2001736, 0, 4127685, 4, { 206.504593f, 77.472130f, -268.054993f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Blueflame_2", 2001737, 0, 4127686, 4, { 204.448807f, 76.131027f, -274.920990f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Klyhiasgrimoire", 2002520, 0, 4322716, 4, { -10.044470f, 67.443398f, 416.002014f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Klyhiasgrimoire_1", 2002521, 0, 4322717, 4, { -10.207020f, 67.504013f, 416.090515f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_0", 2002519, 0, 4322719, 4, { -8.873467f, 66.444923f, 416.840088f }, 1.000000f, -0.929105f, 0); 
    instance.addEObj( "unknown_1", 2001708, 0, 4127472, 4, { 574.117798f, 90.465828f, -429.044006f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_2", 2000608, 2497436, 4324041, 4, { 709.136292f, 66.006943f, -285.714386f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2006339, 0, 5928029, 4, { -148.829193f, 2.922292f, 671.528992f }, 1.000000f, 0.604108f, 0); 
    instance.addEObj( "Stolengoods", 2006340, 0, 5928033, 4, { -148.829300f, 3.515815f, 671.528992f }, 1.300000f, 0.000000f, 0); 
    instance.addEObj( "unknown_4", 2000608, 2379300, 5437049, 4, { -4.575844f, 8.921356f, 837.978821f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_5", 2004812, 0, 5891770, 4, { -189.003906f, 0.070980f, 657.281372f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2001685, 0, 4105788, 4, { 367.294189f, 79.901199f, -366.779205f }, 1.000000f, 0.941436f, 0); 
    instance.addEObj( "unknown_7", 2001729, 0, 4165911, 4, { 278.460693f, 5.865917f, 633.909973f }, 1.000000f, 0.884177f, 0); 
    instance.addEObj( "unknown_8", 2001728, 0, 4174624, 4, { 222.492798f, 14.438920f, 648.959778f }, 1.000000f, 0.155245f, 0); 
    instance.addEObj( "unknown_9", 2001728, 0, 4191046, 4, { 202.207108f, 14.325150f, 643.328186f }, 1.000000f, 0.790309f, 0); 
    instance.addEObj( "unknown_10", 2000608, 2637396, 4324037, 4, { 178.712997f, 14.832550f, 662.518372f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_11", 2000608, 2637395, 4324038, 4, { 196.714005f, 14.832540f, 651.304626f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_12", 2000608, 2636450, 4324039, 4, { 174.509506f, 12.137300f, 635.853882f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_13", 2001891, 0, 4263937, 4, { -8.873500f, 66.444901f, 416.840088f }, 1.000000f, -0.929105f, 0); 
    instance.addEObj( "Destination", 2002010, 0, 4265088, 4, { 108.412003f, 68.131470f, 351.635712f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Megalocrabnest", 2000284, 0, 3629570, 4, { 130.871201f, 36.024380f, 28.531361f }, 0.961271f, 0.000144f, 0); 
    instance.addEObj( "unknown_14", 2001731, 0, 4165916, 4, { 158.098602f, 33.859741f, 92.606934f }, 1.480042f, 0.000048f, 0); 
    instance.addEObj( "unknown_15", 2002717, 0, 4374743, 4, { 156.059998f, 33.990162f, 95.962158f }, 1.500000f, 0.000000f, 0); 
    instance.addEObj( "unknown_16", 2001733, 0, 4165917, 4, { -235.335297f, -0.286180f, 675.433289f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Lavenderpot", 2000296, 0, 3631743, 4, { 565.168884f, 66.695084f, -215.237701f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Fruitbarrel", 2000297, 0, 3631815, 4, { 590.835815f, 72.432549f, -272.082611f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Splinteredcrate", 2000298, 0, 3631817, 4, { 566.855530f, 85.544411f, -320.797089f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Overturnedwain", 2000299, 0, 3631819, 4, { 574.090088f, 90.466743f, -429.068390f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_17", 2001661, 0, 4102376, 4, { 574.273193f, 90.684334f, -428.793793f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_18", 2004367, 0, 4877220, 4, { 507.988098f, 95.965080f, -457.357788f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_19", 2004368, 0, 4877221, 4, { 505.978790f, 97.162064f, -422.457397f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_20", 2004369, 0, 4877222, 4, { 497.169189f, 97.153351f, -408.174988f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_21", 2004860, 0, 5069533, 4, { -148.287399f, -0.347075f, 758.399780f }, 1.000000f, 1.399832f, 0); 
    instance.addEObj( "Destination_1", 2004861, 0, 5069536, 4, { -131.616898f, 0.512191f, 729.980774f }, 1.000000f, 0.555216f, 0); 
    instance.addEObj( "unknown_22", 2004862, 0, 5069540, 4, { 248.654099f, -0.268991f, 662.589600f }, 0.900000f, -0.962715f, 0); 
    instance.addEObj( "unknown_23", 2004910, 0, 5110335, 4, { 242.316101f, 8.000200f, 668.253479f }, 0.700000f, 0.000000f, 0); 
    instance.addEObj( "unknown_24", 2004911, 0, 5110337, 4, { 508.247314f, 95.663528f, -449.799194f }, 1.500000f, 0.000000f, 0); 
    instance.addEObj( "unknown_25", 2004914, 0, 5109579, 4, { 507.661407f, 95.965103f, -448.398499f }, 1.000000f, 0.300543f, 0); 
    instance.addEObj( "unknown_26", 2004915, 0, 5109580, 4, { 507.947113f, 95.965088f, -451.263000f }, 1.000000f, -0.111456f, 0); 
    instance.addEObj( "Entrance_1", 2004304, 0, 4797571, 4, { 272.077087f, 4.403121f, 727.135681f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_27", 2003596, 0, 4629204, 4, { 177.397995f, 0.000000f, 576.364075f }, 1.000000f, -1.392848f, 0); 
    instance.addEObj( "Ratsnest", 2002033, 0, 4286266, 4, { 671.198608f, 64.408203f, -205.249100f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_2", 2002034, 0, 4286899, 4, { 646.172424f, 67.473381f, -263.374908f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_28", 2002633, 0, 4334655, 4, { 648.444397f, 66.958313f, -261.619904f }, 1.000000f, -1.323713f, 0); 
    instance.addEObj( "unknown_29", 2002634, 0, 4334657, 4, { 646.802124f, 67.273483f, -265.729095f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_30", 2002635, 0, 4334658, 4, { 644.529602f, 67.131271f, -261.658813f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_31", 2002636, 0, 4334659, 4, { 649.563416f, 67.201767f, -266.917206f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_32", 2002637, 0, 4334660, 4, { 642.154724f, 67.319054f, -263.312500f }, 1.000000f, -1.145907f, 0); 
    instance.addEObj( "unknown_33", 2002284, 0, 4291539, 4, { 703.640503f, 65.783333f, -288.795685f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance_2", 2003597, 0, 4629203, 4, { 156.319794f, 8.937071f, 580.411621f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_34", 2006298, 0, 5922985, 4, { -97.753693f, 3.097158f, 713.076172f }, 1.000000f, 0.811083f, 0); 
    instance.addEObj( "unknown_35", 2006335, 0, 5939504, 4, { 235.698303f, 7.999100f, 698.232727f }, 1.000000f, -1.520391f, 0); 
    instance.addEObj( "unknown_36", 2006429, 0, 5958507, 4, { 163.285400f, 8.973654f, 583.783691f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_37", 2002559, 0, 4329449, 4, { -70.763161f, 3.078298f, 716.731018f }, 1.000000f, 0.611545f, 0); 
    instance.addEObj( "Weatheredcrate", 2005006, 0, 5392062, 4, { 492.885315f, 68.970558f, -197.584503f }, 0.700000f, 1.082225f, 0); 
    instance.addEObj( "unknown_38", 2005010, 0, 5392066, 4, { 492.885315f, 69.270317f, -197.584503f }, 1.000000f, 1.082224f, 0); 
    instance.addEObj( "Destination_3", 2004935, 0, 5327302, 4, { 19.949850f, 42.933449f, 855.495911f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_4", 2005928, 0, 5895554, 4, { -22.830000f, 66.326103f, 426.170013f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_5", 2005929, 0, 5895555, 4, { -46.680000f, 48.439999f, 529.179993f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_6", 2005930, 0, 5895558, 4, { -93.870003f, 26.940001f, 623.260010f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_7", 2005931, 0, 5895563, 4, { -185.389999f, 0.030906f, 678.840027f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_39", 2006047, 0, 5905149, 4, { 508.768188f, 95.942001f, -450.272308f }, 1.000000f, -1.374122f, 0); 
    instance.addEObj( "Destination_8", 2005942, 0, 5895749, 4, { 122.553200f, 60.681461f, 934.487915f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_40", 2005943, 0, 5895751, 4, { 259.611206f, 4.403100f, 715.393677f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_41", 2001656, 0, 4101363, 4, { 367.294189f, 79.901154f, -366.779205f }, 1.000000f, 0.941436f, 0); 
    instance.addEObj( "unknown_42", 2001807, 0, 4175856, 4, { 389.275513f, 78.356819f, -349.018494f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_43", 2004334, 0, 4797537, 4, { 272.095001f, 0.000000f, 730.797913f }, 1.000000f, -1.014084f, 0); 
    instance.addEObj( "MarkoftheSpinner", 2004592, 0, 4982814, 4, { 251.632599f, 7.449451f, 782.909302f }, 1.000000f, -1.300588f, 0); 
    instance.addEObj( "Destination_9", 2004570, 0, 5578176, 4, { -83.629997f, 1.938600f, 826.115479f }, 1.000000f, 0.676271f, 0); 
    instance.addEObj( "unknown_44", 2004917, 0, 5583532, 4, { -83.629997f, 1.938626f, 826.115479f }, 1.000000f, 0.676272f, 0); 
    instance.addEObj( "unknown_45", 2004859, 0, 5072102, 4, { 569.335205f, 95.546799f, -496.039093f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_10", 2004991, 0, 5388363, 4, { 533.343384f, 103.060303f, -551.280518f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Sackoffleece", 2001487, 0, 4013516, 4, { 476.859192f, 80.205627f, -76.722328f }, 0.991760f, 1.267385f, 0); 
    instance.addEObj( "Damagedwain", 2001489, 0, 4014067, 4, { 254.444107f, 73.350098f, -322.133209f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Damagedwain_1", 2000450, 0, 4219546, 4, { 254.490799f, 73.528419f, -322.200500f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_11", 2001491, 0, 4014784, 4, { 223.468399f, 72.232117f, -283.344788f }, 0.991760f, -1.300299f, 0); 
    instance.addEObj( "Destination_12", 2001492, 0, 4014785, 4, { 247.395096f, 74.782356f, -309.002106f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Pumpkinvine", 2001495, 0, 4031948, 4, { 455.806793f, 68.459877f, -186.845306f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Pumpkinvine_1", 2001496, 0, 4031949, 4, { 472.239685f, 68.398903f, -185.911407f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Pumpkinvine_2", 2001497, 0, 4031950, 4, { 470.683289f, 68.306061f, -173.757294f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Althyklavender", 2001488, 0, 4031958, 4, { 440.570312f, 68.314583f, -176.038300f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Gasplume", 2001500, 0, 4031977, 4, { 278.790009f, 74.949097f, -307.793213f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Gasplume_1", 2001501, 0, 4031978, 4, { 270.250000f, 73.624023f, -263.290009f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Gasplume_2", 2001502, 0, 4031979, 4, { 294.390015f, 73.236237f, -270.220001f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "×SubSea110：荷車1", 2000756, 0, 3767676, 4, { 36.809391f, 71.301613f, 393.422211f }, 1.000000f, 0.613813f, 0); 
    instance.addEObj( "×SubSea110：荷車1_1", 2000756, 0, 3767681, 4, { 48.187561f, 71.274841f, 386.737091f }, 0.991789f, -0.411419f, 0); 
    instance.addEObj( "×SubSea110：荷車1_2", 2000756, 0, 3767687, 4, { 28.997061f, 71.274841f, 399.714111f }, 0.991789f, 0.995057f, 0); 
    instance.addEObj( "×SubSea110：荷車1_3", 2000756, 0, 3767692, 4, { 55.362549f, 71.274841f, 379.783386f }, 0.991789f, -0.894372f, 0); 
    instance.addEObj( "Forecastleplanks", 2000760, 0, 3781381, 4, { 210.112106f, 12.527610f, 591.433899f }, 1.937849f, 1.219198f, 0); 
    instance.addEObj( "Quarterdecklogs", 2000761, 0, 3781382, 4, { 171.588196f, 10.359190f, 589.783081f }, 1.480078f, 0.034275f, 0); 
    instance.addEObj( "Forecastleplanks_1", 2000764, 0, 3871000, 4, { 210.703705f, 11.433180f, 595.810303f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Forecastleplanks_2", 2000765, 0, 3871001, 4, { 218.882401f, 11.117170f, 593.682129f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Packedlunch", 2000762, 0, 3781642, 4, { 217.341095f, 8.973405f, 606.443420f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "Packedlunch_1", 2000763, 0, 3781643, 4, { 287.164795f, 32.204010f, 607.054321f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "×SubSea116：焚火1", 2000766, 0, 3781659, 4, { 249.994995f, 6.222380f, 772.705811f }, 0.900235f, 1.543922f, 0); 
    instance.addEObj( "×SubSea116：焚火2", 2000767, 0, 3781662, 4, { 249.957993f, 6.371591f, 775.265015f }, 0.900235f, 0.000623f, 0); 
    instance.addEObj( "unknown_46", 2001730, 0, 4234827, 4, { 167.579300f, 14.095910f, 683.943481f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Brasshelmwheel", 2000769, 0, 3781818, 4, { -145.094696f, 1.071958f, 709.132385f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "Tangledrigging", 2000770, 0, 3781824, 4, { -185.682098f, -0.117385f, 694.673828f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Foldedsailcloth", 2000771, 0, 3781825, 4, { -168.841095f, 1.974134f, 659.327026f }, 0.961271f, 0.000144f, 0); 
    instance.addEObj( "Suspicioushole", 2000772, 0, 3781879, 4, { 97.927467f, 20.646410f, 773.437622f }, 0.869751f, 0.000527f, 0); 
    instance.addEObj( "Suspicioushole_1", 2000773, 0, 3782137, 4, { 46.715172f, 30.712959f, 756.489014f }, 0.808655f, -1.519958f, 0); 
    instance.addEObj( "Suspicioushole_2", 2000774, 0, 3782147, 4, { 94.602097f, 24.773520f, 820.623718f }, 0.808655f, -0.815275f, 0); 
    instance.addEObj( "LaNosceanlilybell", 2000775, 0, 3782531, 4, { 36.162552f, 46.979881f, 716.528320f }, 0.808681f, 0.944131f, 0); 
    instance.addEObj( "LaNosceanlilybell_1", 2000776, 0, 3782535, 4, { 58.650291f, 43.403648f, 692.919312f }, 0.839199f, 0.272780f, 0); 
    instance.addEObj( "LaNosceanlilybell_2", 2000777, 0, 3782540, 4, { 68.917198f, 46.204788f, 676.176086f }, 0.869717f, 1.012555f, 0); 

  }

  void onPlayerSetup( Sapphire::QuestBattle& instance, Entity::Player& player ) override
  {
    player.setRot( 0 );
    player.setPos( { -60, 25, -135 } );
  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {
    auto set1Spawned = instance.getDirectorVar( Variables::SET_1_SPAWNED );
    auto set2Spawned = instance.getDirectorVar( Variables::SET_2_SPAWNED );
    auto successCalled = instance.getDirectorVar( Variables::SUCCESS_CALLED );

    auto boss = instance.getActiveBNpcByLayoutId( INIT_POP_BOSS );
    auto ysthola = instance.getActiveBNpcByLayoutId( INIT_P_POP_01 );
    auto pPlayer = instance.getPlayerPtr();

    auto bossHp = boss ? boss->getHpPercent() : 0;

    if( pPlayer && !pPlayer->isAlive() )
    {
      instance.fail();
      return;
    }

    if( !set1Spawned && bossHp <= 75 )
    {
      auto a1 = instance.createBNpcFromLayoutId( INIT_POP_01_01, 100, Common::BNpcType::Enemy );
      auto a2 = instance.createBNpcFromLayoutId( INIT_POP_01_02, 100, Common::BNpcType::Enemy );

      a1->setFlag( Entity::NoDeaggro );
      a2->setFlag( Entity::NoDeaggro );

      a1->hateListAdd( pPlayer, 1 );
      a2->hateListAdd( pPlayer, 1 );

      instance.setDirectorVar( Variables::SET_1_SPAWNED, true );
    }

    if( !set2Spawned && bossHp <= 25 )
    {
      auto a3 = instance.createBNpcFromLayoutId( INIT_POP_02_01, 150, Common::BNpcType::Enemy );
      auto a4 = instance.createBNpcFromLayoutId( INIT_POP_02_02, 150, Common::BNpcType::Enemy );
      auto a5 = instance.createBNpcFromLayoutId( INIT_POP_02_03, 100, Common::BNpcType::Enemy );
      auto a6 = instance.createBNpcFromLayoutId( INIT_POP_02_04, 100, Common::BNpcType::Enemy );

      a3->setFlag( Entity::NoDeaggro );
      a4->setFlag( Entity::NoDeaggro );
      a5->setFlag( Entity::NoDeaggro );
      a6->setFlag( Entity::NoDeaggro );

      a3->hateListAdd( pPlayer, 1 );
      a4->hateListAdd( pPlayer, 1 );
      a5->hateListAdd( pPlayer, 1 );
      a6->hateListAdd( pPlayer, 1 );

      instance.setDirectorVar( Variables::SET_2_SPAWNED, true );
    }

    if( !successCalled && instance.getCountEnemyBNpc() == 0 )
    {
      instance.setDirectorVar( Variables::SUCCESS_CALLED, true );
      instance.success();
    }
  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {
    eventMgr().playScene( player, instance.getDirectorId(), 1,
                      NO_DEFAULT_CAMERA | CONDITION_CUTSCENE | SILENT_ENTER_TERRI_ENV |
                      HIDE_HOTBAR | SILENT_ENTER_TERRI_BGM | SILENT_ENTER_TERRI_SE |
                      DISABLE_STEALTH | 0x00100000 | LOCK_HUD | LOCK_HOTBAR |
                      // todo: wtf is 0x00100000
                      DISABLE_CANCEL_EMOTE, [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.setOnEnterEventDone( true );
                      } );
  }

  void onDutyComplete( QuestBattle& instance, Entity::Player& player ) override
  {
    auto idx = player.getQuestIndex( instance.getQuestId() );
    if( idx == -1 )
      return;
    auto& quest = player.getQuestByIndex( idx );
    quest.setSeq( 2 );
  }

  void onDutyCommence( QuestBattle& instance, Entity::Player& player ) override
  {
    auto boss = instance.createBNpcFromLayoutId( INIT_POP_BOSS, 2000, Common::BNpcType::Enemy );
    auto ysthola = instance.createBNpcFromLayoutId( INIT_P_POP_01, 27780, Common::BNpcType::Friendly );
    
    boss->setFlag( Entity::NoDeaggro );
    ysthola->setFlag( Entity::NoDeaggro );

    boss->hateListAdd( ysthola, 10000 );
    boss->hateListAdd( player.getAsPlayer(), 1 );

    ysthola->hateListAdd( boss, 10000 );
  }

};

EXPOSE_SCRIPT( LurkersintheGrotto );