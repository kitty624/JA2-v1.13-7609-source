﻿// WANNE: Yes, this should be disabled, otherwise we get weird behavior when running the game with a VS 2005 build!
//#pragma setlocale("RUSSIAN")

#ifdef PRECOMPILEDHEADERS
	#include "Utils All.h"
	#include "_Ja25RussianText.h"
#else
	#include "Language Defines.h"
	#ifdef RUSSIAN
		#include "text.h"
		#include "Fileman.h"
	#endif
#endif

//suppress : warning LNK4221: no public symbols found; archive member will be inaccessible
void this_is_the_Ja25RussianText_public_symbol(void){;}

#ifdef RUSSIAN

// VERY TRUNCATED FILE COPIED FROM JA2.5 FOR ITS FEATURES FOR JA2 GOLD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SANDRO - New STOMP laptop strings
//these strings match up with the defines in IMP Skill trait.cpp
STR16 gzIMPSkillTraitsText[]=
{
	// made this more elegant
	L"Взлом замков",
	L"Рукопашный бой",
	L"Электроника",
	L"Ночник",
	L"Метание",
	L"Инструктор",
	L"Тяжелое оружие",
	L"Автоматическое оружие",
	L"Скрытность",
	L"Ловкач",
	L"Холодное оружие",
	L"Снайпер",
	L"Камуфляж",
	L"Боевые искусства",

	L"Нет",
	L"I.M.P.: Специализация",
	L"(эксперт)",

};

//added another set of skill texts for new major traits
STR16 gzIMPSkillTraitsTextNewMajor[]=
{
	L"Автоматчик",	//Auto Weapons
	L"Гренадёр",	//Heavy Weapons
	L"Стрелок",	//Marksman
	L"Охотник",	//Hunter
	L"Ковбой",	//Gunslinger
	L"Боксёр",	//Hand to Hand
	L"Старшина",	//Deputy
	L"Механик-электронщик",	//Technician
	L"Санитар",	//Paramedic
	L"Тайные операции",	//Covert Ops

	L"Нет",
	L"I.M.P.: Основные навыки",	//I.M.P. Major Traits
	// second names
	L"Пулемётчик",	//Machinegunner
	L"Артиллерист",	//Bombardier
	L"Снайпер",	//Sniper
	L"Егерь",	//Ranger
	L"Пистолетчик",	//Gunfighter
	L"Боевые искусства",	//Martial Arts
	L"Командир",	//Squadleader
	L"Инженер",	//Engineer
	L"Доктор",	//Doctor
	L"Шпион",	//Spy
};

//added another set of skill texts for new minor traits
STR16 gzIMPSkillTraitsTextNewMinor[]=
{
	L"Ловкач",	//Ambidextrous
	L"Мастер клинка",	//Melee
	L"Мастер по метанию",	//Throwing
	L"Ночник",	//Night Ops
	L"Бесшумный убийца",	//Stealthy
	L"Спортсмен",	//Athletics
	L"Культурист",	//Bodybuilding
	L"Подрывник",	//Demolitions
	L"Инструктор",	//Teaching
	L"Разведчик",	//Scouting
	L"Радист",

	L"Нет",
	L"I.M.P.: Дополнительные навыки",	//I.M.P. Minor Traits
};

//these texts are for help popup windows, describing trait properties
STR16 gzIMPMajorTraitsHelpTextsAutoWeapons[]=
{
	L"+%d%s к шансу попадания из автомата\n",
	L"+%d%s к шансу попадания из пистолет-пулемёта\n",
	L"+%d%s к шансу попадания из ручного пулемёта\n",
	L"-%d%s ОД на стрельбу из ручного пулемёта в\nрежиме автоматической стрельбы или очередью с отсечкой\n",
	L"-%d%s ОД на вскидывание ручного пулемёта\n",
	L"Штраф на шанс попадания в автоматическом\nрежиме огня и в режиме очереди понижен на %d%s\n",
	L"Понижен шанс лишних выстрелов при автоматической стрельбе\n",

};
STR16 gzIMPMajorTraitsHelpTextsHeavyWeapons[]=
{
	L"-%d%s ОД на стрельбу из гранатомёта\n",
	L"-%d%s ОД на стрельбу из реактивного гранатомёта\n",
	L"+%d%s к шансу попадания из гранатомёта\n",
	L"+%d%s к шансу попадания из реактивного гранатомёта\n",
	L"-%d%s ОД на залп из миномёта\n",
	L"Понижен штраф на шанс попадания при стрельбе с миномёта на %d%s\n",
	L"+%d%s к урону танкам от тяжёлого оружия, гранат и взрывчатки\n",
	L"+%d%s к урону иным целям из тяжёлого оружия\n",

};
STR16 gzIMPMajorTraitsHelpTextsSniper[]=
{
	L"+%d%s к шансу попадания из винтовки\n",
	L"+%d%s к шансу попадания из снайперской винтовки\n",
	L"-%d%s эффективной дальности до цели для всего вида оружия\n",	//-%d%s effective range to target with all weapons
	L"+%d%s к бонусу прицеливания на каждый клик прицеливания (за исключением пистолетов)\n",
	L"+%d%s к повреждению от выстрела",	//+%d%s damage on shot
	L" плюс",
	L" с каждым кликом",
	L" после первого",
	L" после второго",
	L" после третьего",
	L" после четвёртого",
	L" после пятого",
	L" после шестого",
	L" после седьмого",
	L"-%d%s ОД на досылание патрона в винтовки со скользящим затвором\n",
	L"+1 клик прицеливания для оружия типа винтовок\n",
	L"+%d кликов прицеливания для оружия типа винтовок\n",
	L"Прицеливание оружия типа винтовок быстрее на один клик прицеливания\n",
	L"Прицеливание оружия типа винтовок быстрее на %d кликов прицеливания\n",

};
STR16 gzIMPMajorTraitsHelpTextsRanger[]=
{
	L"+%d%s к шансу попадания из винтовки\n",
	L"+%d%s к шансу попадания из дробовика\n",
	L"-%d%s ОД на перезарядку помпового дробовика\n",
	L"-%d%s ОД на выстрел из дробовика\n",
	L"+%d клик прицеливания для дробовиков\n",
	L"+%d кликов прицеливания для дробовиков\n",
	L"+%d%s к скорости передвижения группы между секторами, если идти пешком\n",
	L"+%d%s к скорости передвижения группы между секторами, \nесли передвигаться на транспорте (за исключением вертолёта)\n",
	L"-%d%s к затрате энергии при переходе между секторами\n",	//меньше тратит сил
	L"-%d%s к штрафам от погодных условий\n",
	L"+%d%s к эффективности камуфляжа\n",
	L"-%d%s на скорость ухудшения камуфляжа от воды и времени\n",

};
STR16 gzIMPMajorTraitsHelpTextsGunslinger[]=
{
	L"-%d%s ОД на выстрел из пистолетов и револьверов\n",
	L"+%d%s к эффективной дальности пистолетов и револьверов\n",
	L"+%d%s к шансу попадания из пистолетов и револьверов\n",
	L"+%d%s к шансу попадания из автоматических пистолетов",
	L" (только для одиночного выстрела)",
	L"+%d%s бонуса на один клик прицеливания для пистолетов,\nавтоматических пистолетов и револьверов\n",
	L"-%d%s ОД на вскидывание пистолетов и револьверов\n",
	L"-%d%s ОД на перезарядку пистолетов, автоматических пистолетов и револьверов\n",
	L"+%d клик прицеливания для пистолетов, автоматических пистолетов и револьверов",
	L"+%d кликов прицеливания для пистолетов, автоматических пистолетов и револьверов\n",

};
STR16 gzIMPMajorTraitsHelpTextsMartialArts[]=
{
	L"-%d%s ОД на рукопашные атаки (кулаками и кастетом)\n",
	L"+%d%s к шансу на результативный удар рукой\n",
	L"+%d%s к шансу на результативный удар кастетом\n",
	L"+%d%s к урону в рукопашных атаках (кулаками и кастетом)\n",
	L"+%d%s к урону выносливости в рукопашных атаках (кулаками и кастетом)\n",
	L"Враг, сваленный вашими ударами, немного дольше приходит в себя\n",
	L"Враг, сваленный вашими ударами, дольше приходит в себя\n",
	L"Враг, сваленный вашими ударами, намного дольше приходит в себя\n",
	L"Враг, сваленный вашими ударами, очень долго приходит в себя\n",
	L"Враг, сваленный вашими ударами, надолго теряет сознание\n",
	L"Враг, сваленный вашими ударами, теряет сознание на много часов\n",
	L"Враг, сваленный вашими ударами, вероятно, больше не очнётся\n",
	L"Прицельный удар наносит на %d%s больше урона\n",
	L"Удар ногой с разворота наносит на %d%s больше урона\n",
	L"+%d%s к шансу увернуться от атаки в рукопашном бою\n",
	L"+%d%s к шансу увернуться от удара рукой",
	L" или кастетом",
	L" (+%d%s с кастетом)",
	L"+%d%s к шансу увернуться от удара кастетом\n",
	L"+%d%s к шансу увернуться от атаки любым оружием ближнего боя\n",
	L"Нужно на %d%s ОД меньше, чтобы выхватить оружие из рук противника\n",
	L"Нужно на %d%s ОД меньше, чтобы сменить положение (стоя, сидя, лежа), повернуться, слезть/залезть на крышу и перепрыгнуть препятствие\n",
	L"Нужно на %d%s ОД меньше, чтобы сменить положение (стоя, сидя, лежа)\n",
	L"Нужно на %d%s ОД меньше, чтобы повернуться\n",
	L"Нужно на %d%s ОД меньше, чтобы слезть/залезть на крышу и перепрыгнуть препятствие\n",
	L"+%d%s к шансу выбить дверь ногой\n",
	L"Вы получаете специальные движения для атак ближнего боя\n",
	L"-%d%s к шансу перехвата вашего хода во время движения\n", //chance to be interrupted when moving

};
STR16 gzIMPMajorTraitsHelpTextsSquadleader[]=
{
	L"+%d%s ОД на каждый ход рядом находящимся наёмникам\n",
	L"+%d к фактическому уровню рядом находящихся наёмников, у которых уровень ниже, чем у %s\n",
	L"+%d к фактическому уровню опыта союзников при подсчете бонуса подавления для их огня\n",
	L"На +%d%s труднее подавить %s и наёмников рядом с ним\n",
	L"+%d к боевому духу рядом находящихся наёмников\n",
	L"-%d к потере боевого духа для рядом находящихся наёмников\n",
	L"Радиус влияния на других наёмников составляет %d тайлов",
	L" (%d тайлов с усилителем звука)",
	L"(Максимальное количество одновременных бонусов для одного солдата %d)\n",
	L"+%d%s сопротивление страху у %s\n",
	L"Недостаток: %dx кратное ухудшение боевого духа у наёмников, если погибает %s\n",
	L"+%d%s к шансу получить перехват всем отрядом\n",

};
STR16 gzIMPMajorTraitsHelpTextsTechnician[]=
{
	L"+%d%s к скорости ремонта\n",
	L"+%d%s к умению взлома замков (обычных/электронных)\n",
	L"+%d%s к умению отключать электронные ловушки\n",
	L"+%d%s к умению сборки вещей и присоединению особых деталей\n",
	L"+%d%s к умению устранить осечку оружия в бою\n",
	L"Понижен штраф на ремонт электронных предметов на %d%s\n",
	L"Повышен шанс обнаружить электронные ловушки и мины (+%d к уровню обнаружения)\n",
	L"+%d%s к шансу попадания по цели роботу, управляемому %s\n",
	L"%s даёт возможность ремонтировать робота\n",
	L"Понижен штраф на скорость ремонта робота на %d%s\n",
};
STR16 gzIMPMajorTraitsHelpTextsDoctor[]=
{
	L"Может выполнять хирургические операции при наличии медицинской сумки\n",
	L"Хирургическая операция возвращает %d%s единиц потерянного здоровья.",
	L" (Требует значительного расхода содержимого мед. сумки.)",
	L"Может вернуть ухудшившиеся навыки (вследствие критического ранения) путём",
	L" хирургического вмешательства или",
	L" обычным лечением.\n",
	L"+%d%s к эффективности при связке доктор-пациент\n",
	L"+%d%s к скорости перевязки\n",
	L"+%d%s к природной скорости регенерации для всех солдат в том же секторе",
	L" (максимум %d бонуса на находящихся в секторе)",
};
STR16 gzIMPMajorTraitsHelpTextsCovertOps[]=
{
	L"Может переодеваться в гражданского или солдата, \nчтобы проникать в тыл врага.\n",
	L"Будет раскрыт, если совершает подозрительные действия, \nимеет подозрительное снаряжение или застигнут над остывающим трупом.\n",
	L"Будет моментально раскрыт, если переодет в солдата \nи находится ближе %d тайлов к врагу.\n",
	L"Будет моментально раскрыт, если переодет в солдата \nи находится ближе %d тайлов к остывающему трупу.\n",
	L"+%d%s к шансу попадания скрытным оружием ближнего боя.\n",
	L"+%d%s к шансу на смертельный удар скрытным оружием ближнего боя.\n",
	L"ОД на переодевание снижены на %d%s.\n",
};

STR16 gzIMPMajorTraitsHelpTextsRadioOperator[]=
{
	L"Может использовать оборудование связи.\n", 
	L"Может запрашивать артиллерийские удары у союзников в соседних секторах.\n",
	L"Может обнаруживать вражеские патрули при сканировании частот.\n",
	L"Радиопереговоры могут быть подавлены во всем секторе.\n",
	L"Если радиопереговоры подавлены, то радист может искать подавляющее устройство.\n",
	L"Может вызывать подкрепления из отрядов ополченцев из соседних секторов.\n",
};

STR16 gzIMPMajorTraitsHelpTextsNone[]=
{
	L"Нет преимуществ",
};

STR16 gzIMPMinorTraitsHelpTextsAmbidextrous[]=
{
	L"Понижен штраф на стрельбу с двух рук на %d%s\n",
	L"+%d%s к скорости на перезарядку оружия магазином\n",
	L"+%d%s к скорости на дозарядку магазина оружия\n",
	L"-%d%s ОД, чтобы поднять предмет\n",
	L"-%d%s ОД на манипуляции с рюкзаком\n",
	L"-%d%s ОД на действия с дверью\n",
	L"-%d%s ОД, необходимых для установки/обезвреживания бомб и мин\n",
	L"-%d%s ОД, необходимых на присоединение навески\n",
};
STR16 gzIMPMinorTraitsHelpTextsMelee[]=
{
	L"-%d%s ОД на атаку клинковым оружием\n",
	L"+%d%s к шансу попадания клинковым холодным оружием\n",
	L"+%d%s к шансу попадания дробящим холодным оружием\n",
	L"+%d%s к урону от клинкового холодного оружия\n",
	L"+%d%s к урону от дробящего холодного оружия\n",
	L"Урон от прицельной атаки любым холодным оружием повышается на %d%s\n",
	L"+%d%s к шансу уклониться от атаки клинковым холодным оружием\n",
	L"+%d%s к шансу уклониться от атаки клинковым холодным оружием, если в руках нож\n",
	L"+%d%s к шансу уклониться от атаки дробящим холодным оружием\n",
	L"+%d%s к шансу уклониться от атаки дробящим холодным оружием, если в руках нож\n",

};
STR16 gzIMPMinorTraitsHelpTextsThrowing[]=
{
	L"-%d%s базовых ОД, нужных для броска ножа\n",
	L"+%d%s к максимальной эффективной дальности броска ножа\n",
	L"+%d%s к шансу попадания в цель при метании ножа\n",
	L"+%d%s к шансу попадания в цель при метании ножа на каждый клик прицеливания\n",
	L"+%d%s к урону от метательного ножа\n",
	L"+%d%s к урону от метательного ножа при на каждый клик прицеливания\n",
	L"+%d%s к шансу нанести критический урон при броске ножа, если вас не слышали и не видели\n",
	L"+%d к множителю критического урона при броске ножа\n",
	L"+%d клик прицеливания для метательных ножей\n",
	L"+%d кликов прицеливания для метательных ножей\n",

};
STR16 gzIMPMinorTraitsHelpTextsNightOps[]=
{
	L"+%d к зрению в темноте\n",
	L"+%d к дальности слуха\n",
	L"+%d дополнительно к слуху в темноте\n",
	L"+%d к вероятности перехвата хода в ночи\n",
	L"-%d к нужде во сне\n",

};
STR16 gzIMPMinorTraitsHelpTextsStealthy[]=
{
	L"-%d%s ОД, необходимых для бесшумного передвижения\n",
	L"+%d%s к шансу двигаться бесшумно\n",
	L"+%d%s к скрытности (быть 'невидимым', если вас не обнаружили)\n",
	L"Штраф укрытия при передвижении уменьшен на %d%s\n",
	L"-%d%s к шансу быть перехваченным\n", //chance to be interrupted

};
STR16 gzIMPMinorTraitsHelpTextsAthletics[]=
{
	L"-%d%s ОД на передвижение (бег, шаг, шаг вприсядку, переползание, плавание и т.д.)\n",
	L"-%d%s на затраты энергии при движении, вскарабкивание на крышу, прыжки через препятствия, плавание и т.д.\n",
};
STR16 gzIMPMinorTraitsHelpTextsBodybuilding[]=
{
	L"Имеет %d%s устойчивости к повреждениям\n",
	L"+%d%s к силе для определения максимально допустимого веса\n",
	L"Потеря сил при пропущенных ударах в ближнем бою уменьшена на %d%s\n",
	L"Урон при ранении в ногу, при котором вы падаете на землю, должен быть больше на %d%s\n",

};
STR16 gzIMPMinorTraitsHelpTextsDemolitions[]=
{
	L"-%d%s ОД для броска гранаты\n",
	L"+%d%s к максимальной дальности броска гранаты\n",
	L"+%d%s к точности броска гранаты\n",
	L"+%d%s к урону для установленных бомб и мин\n",
	L"+%d%s к умению устанавливать детонатор\n",
	L"+%d%s к установке/разминированию бомб\n",
	L"Уменьшает шанс обнаружения противником установленных вами бомб и мин (+%d к уровню бомб)\n",
	L"Повышает вероятность вскрытия замка формовым зарядом (урон увеличен на %d)\n",

};
STR16 gzIMPMinorTraitsHelpTextsTeaching[]=
{
	L"+%d%s к скорости обучения ополчения\n",
	L"+%d%s к фактическому навыку лидерства при обучении ополчения\n",
	L"+%d%s к скорости обучения других наёмников\n",
	L"Значение уровня умения будет выше на +%d при обучении другого бойца этому умению\n",
	L"+%d%s к скорости самостоятельного обучения/тренировке\n",

};
STR16 gzIMPMinorTraitsHelpTextsScouting[]=
{
	L"+%d к эффективной прицельной видимости для оружия с оптическими прицелами\n",
	L"+%d к эффективной дальности видимости для биноклей (и оптических прицелов, отсоединённых от оружия)\n",
	L"-%d от туннельного зрения для биноклей (и оптических прицелов, отсоединённых от оружия)\n",
	L"В секторах, смежных с вашим, будет показано точное количество врагов\n",
	L"В секторах, смежных с вашим, будет показано наличие врагов\n",
	L"Предотвращает попадание отряда во вражеские засады\n",
	L"Предотвращает попадание отряда в засады кошек-убийц\n",
};
STR16 gzIMPMinorTraitsHelpTextsSnitch[]=
{
	L"Иногда будет оповещать вас о мнениях членов команды.\n",
	L"Предотвращает плохое поведение членов команды (наркотики, алкоголь, воровство).\n",
	L"Может заниматься пропагандой в городах.\n",
	L"Может собирать слухи в городах.\n",
	L"Можно засылать в качестве доносчика в тюрьмы.\n",
	L"Увеличивает вашу репутацию на %d каждый день, если его боевой дух высок.\n",
	L"+%d фактической дальности слуха.\n",
	
};
STR16 gzIMPMinorTraitsHelpTextsNone[]=
{
	L"Нет преимуществ",
};

STR16 gzIMPOldSkillTraitsHelpTexts[]=
{
	L"+%d%s бонус ко взлому замков\n",
	L"+%d%s к точности удара в рукопашной схватке\n",
	L"+%d%s к повреждениям в рукопашной схватке\n",
	L"+%d%s к шансу уклониться от удара кулака в рукопашной схватке\n",
	L"Нет штрафа для ремонта и использования электронных устройств \n(замков, ловушек, детонаторов, робота и т.д.)\n",
	L"+%d к зрению в темноте\n",
	L"+%d к дальности слуха\n",
	L"+%d дополнительно к слуху в темноте\n",
	L"+%d к вероятности перехвата хода в ночи\n",
	L"-%d к нужде во сне\n",
	L"+%d%s к максимальной дальности при метании чего угодно\n",
	L"+%d%s к шансу попадания при метании чего угодно\n",
	L"+%d%s к шансу мгновенно убить метательным ножом, если вас никто не заметил и не услышал\n",
	L"+%d%s к скорости обучения ополчения или других наемников\n",
	L"+%d%s к фактическому навыку лидерства при обучении ополчения\n",
	L"+%d%s к шансу попадания из гранатомёта, реактивного гранатомёта и миномёта\n",
	L"Штраф на вероятность поражения цели при стрельбе очередью понижен на %d\n",
	L"Понижен шанс лишних выстрелов при автоматической стрельбе\n",
	L"+%d%s к бесшумному передвижению\n",
	L"+%d%s к скрытности (быть 'невидимым', если вас не обнаружили)\n",
	L"Нет штарафа на шанс попадания по цели при стрельбе с двух рук\n",
	L"+%d%s к шансу попадания клинковым холодным оружием\n",
	L"+%d%s к шансу уклониться от удара клинковым холодным оружием, если в руках есть нож\n",
	L"+%d%s к шансу уклониться от удара клинковым холодным оружием, если в руках не нож\n",
	L"+%d%s к шансу уклониться от удара оружием ближнего боя, если в руках есть нож\n",
	L"-%d%s к эффективной дальности до цели для всего вида оружия\n",
	L"+%d%s к бонусу прицеливания на каждый клик прицеливания\n",
	L"Несмываемый камуфляж.\n",
	L"+%d%s к шансу попадания в ближнем бою\n",
	L"+%d%s к урону в ближнем бою\n",
	L"+%d%s к шансу уклониться от атаки в ближнем бою, если в руках ничего нет\n",
	L"+%d%s к шансу уклониться от атаки в ближнем бою, если руки заняты\n",
	L"+%d%s к шансу уклониться от атаки клинковым холодным оружием\n",
	L"Способен нанести удар ногой с разворота по ослабленному противнику с нанесением двойного урона\n",
	L"У вас будет особая анимация ударов в ближнем бою.\n",
	L"Нет преимуществ",
};

STR16 gzIMPNewCharacterTraitsHelpTexts[]=
{
//I.M.P. Character Traits help text
	L"плюсы: Нет преимуществ.\n \nминусы: Без изъянов.",	//Neutral
	L"плюсы: Лучше работает в команде.\n \nминусы: Боевой дух не растёт, когда наёмник работает один.",	//Sociable
	L"плюсы: Лучше работает в одиночестве.\n \nминусы: Боевой дух не растёт в присутствии других бойцов.",	//Loner
	L"плюсы: Боевой дух растет быстрее, а снижается медленнее обычного.\n \nминусы: Шанс обнаружить мины и ловушки ниже среднего.",	//Optimist
	L"плюсы: Лучше ладит с людьми и тренирует ополчение.\n \nминусы: Действия других бойцов не влияют на его боевой дух.",	//Assertive
	L"плюсы: Немного быстрее обучается при самоподготовке или в качестве ученика.\n \nминусы: Обладает меньшим сопротивлением страху и подавлению.",	//Intellectual
	L"плюсы: Устаёт медленнее других, если работает не как врач, ремонтник, тренер или ученик.\n \nминусы: Его мудрость, лидерство, взрывное дело, механика и медицина растут медленнее обычного.",	//Primitive
	L"плюсы: Немного большие шанс попадания при стрельбе очередями и урон в рукопашной. \nПри убийстве врага боевой дух растёт больше, чем у других.\n \nминусы: Хуже исполняет обязанности, для которых требуется терпение: \nремонт, вскрытие замков, снятие ловушек, лечение, тренировка ополчения.",	//Aggressive
	L"плюсы: Лучше исполняет обязанности, требующие терпения: \nремонт, вскрытие замков, снятие ловушек, лечение, тренировка ополчения.\n \nминусы: Имеет меньший шанс перехватить ход врага.",	//Phlegmatic
	L"плюсы: Имеет повышенное сопротивление подавлению и страху. \nБоевой дух при ранениях и гибели товарищей понижается медленнее, чем у других.\n \nминусы: Может быть с большей вероятностью поражен во время движения.",	//Dauntless
	L"плюсы: Боевой дух повышается при выполнении небоевых заданий (кроме тренировки ополчения).\n \nминусы: Убийство врагов не повышает боевой дух.",	//Pacifist
	L"плюсы: Имеет больший шанс нанести болезненные раны и травмы, приводящие к ухудшению параметров.\nБоевой дух повышается при нанесении таких ран.\n \nминусы: Имеет проблемы в общении и быстро теряет боевой дух, если не сражается.",	//Malicious
	L"плюсы: Лучше работает в компании представителей противоположного пола.\n \nминусы: Боевой дух бойцов того же пола в его присутствии растёт медленнее.",	//Show-off
};

STR16 gzIMPDisabilitiesHelpTexts[]=
{
	L"Никакого влияния.",
	L"Уменьшается работоспособность и возникают проблемы с дыханием, \nесли находится в пустынной или тропической местности.",
	L"Может впасть в панику, если оставить одного в определённых ситуациях.",
	L"Понижается работоспособность в подземельях.",
	L"При попытке плыть может с лёгкостью утонуть.",
	L"При виде больших насекомых может впасть в крайности и наворотить дел... \nНахождение в тропических лесах также слегка понижает его работоспособность.",
	L"Иногда забывает приказы, из-за чего теряет \nнекоторое количество ОД во время боя.",
	L"Иногда бывают приступы помутнения рассудка. \nВ такие моменты он расстреливает весь магазин до последней пули. \nПадает духом, если его оружие этого не позволяет.",
	L"Значительно пониженный слух.",
	L"Сниженная дальность видимости.",
};



STR16 gzIMPProfileCostText[]=
{
	L"Составление вашей харрактеристики стоит $%d. Подтвердить оплату?",
};

STR16 zGioNewTraitsImpossibleText[]=
{
	L"Нельзя выбрать новые умения IMP персонажа с отключенным PROFEX. Проверьте значение файла настроек JA2_Options.ini, ключ: READ_PROFILE_DATA_FROM_XML.",
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//@@@:  New string as of March 3, 2000.
STR16	gzIronManModeWarningText[]=
{
	L"Ваш выбор позволит сохраняться лишь в \"мирное время\". Проходить игру станет гораздо сложнее, так как сохраняться вы сможете только между боями. После старта игры изменить эту настройку нельзя. Вы уверены, что готовы расстаться с возможностью сохраняться в бою?",
};

STR16 gzDisplayCoverText[]=
{
	L"Укрытие: %d/100 %s, освещённость: %d/100",
	L"Дальнобойность оружия: %d/%d тайлов, шанс попадания: %d/100",
	L"Дальнобойность оружия: %d/%d тайлов, твердость руки: %d/100",
	L"Отключено выделение видимых зон наёмника и врага",
	L"Видимые зоны наёмника",
	L"Опасные зоны для наёмника",
	L"Лес", //Wood //wanted to use jungle , but wood is shorter in german too (dschungel vs wald)
	L"Город",
	L"Пустыня",
	L"Снег",	//NOT USED!!!
	L"Лес и пустыня",
	L"" // yes empty for now
};

#endif
