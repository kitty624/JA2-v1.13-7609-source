#ifdef PRECOMPILEDHEADERS
	#include "TileEngine All.h"
#else
	#include "sgp.h"
	#include "lighting.h"
	#include "environment.h"
	#include "renderworld.h"
	#include "Sound Control.h"
	#include "overhead.h"
	#include "Game Clock.h"
	#include "quests.h"
	#include "Ambient Control.h"
	#include "Strategic Event Handler.h"
	#include "BobbyR.h"
	#include "mercs.h"
	#include "email.h"
	#include "Merc Hiring.h"
	#include "insurance Contract.h"
	#include "Game Events.h"
	#include "message.h"
	#include "opplist.h"
	#include "Random.h"
	#include "strategicmap.h"
	#include "GameSettings.h"
#endif

#include "Text.h"
#include "connect.h"

//effects whether or not time of day effects the lighting.	Underground
//maps have an ambient light level that is saved in the map, and doesn't change.
BOOLEAN			gfBasement = FALSE;
BOOLEAN			gfCaves = FALSE;


#define	ENV_TOD_FLAGS_DAY										0x00000001
#define	ENV_TOD_FLAGS_DAWN									0x00000002
#define	ENV_TOD_FLAGS_DUSK									0x00000004
#define	ENV_TOD_FLAGS_NIGHT									0x00000008

/*
#define		DAWNLIGHT_START											( 5 * 60 )
#define		DAWN_START													( 6 * 60 )
#define	DAY_START														( 8 * 60 )
#define		TWILLIGHT_START											( 19 * 60 )
#define		DUSK_START													( 20 * 60 )
#define	NIGHT_START													( 22 * 60 )
*/
#define		DAWN_START													( 6 * 60 + 47 )		//6:47AM
#define	DAY_START														( 7 * 60 + 5 )		//7:05AM
#define		DUSK_START													( 20 * 60 + 57 )	//8:57PM
#define	NIGHT_START													( 21 * 60 + 15 )	//9:15PM

#define		DAWN_TO_DAY													(DAY_START-DAWN_START)
#define		DAY_TO_DUSK													(DUSK_START-DAY_START)
#define		DUSK_TO_NIGHT												(NIGHT_START-DUSK_START)
#define		NIGHT_TO_DAWN												(24*60-NIGHT_START+DAWN_START)

UINT32										guiEnvWeather	= 0;
UINT32										guiRainLoop	= NO_SAMPLE;


// frame cues for lightning
UINT8 ubLightningTable[3][10][2]=
																{	{	{0,	15},
																		{1, 0},
																		{2, 0},
																		{3, 6},
																		{4, 0},
																		{5, 0},
																		{6, 0},
																		{7, 0},
																		{8, 0},
																		{9, 0}	},

																	{	{0,	15},
																		{1, 0},
																		{2, 0},
																		{3, 6},
																		{4, 0},
																		{5, 15},
																		{6, 0},
																		{7, 6},
																		{8, 0},
																		{9, 0}	},

																	{	{0,	15},
																		{1, 0},
																		{2, 15},
																		{3, 0},
																		{4, 0},
																		{5, 0},
																		{6, 0},
																		{7, 0},
																		{8, 0},
																		{9, 0}	}	};

// CJC: I don't think these are used anywhere!
UINT8			guiTODFlags[ENV_NUM_TIMES] = {
																			ENV_TOD_FLAGS_NIGHT,		// 00
																			ENV_TOD_FLAGS_NIGHT,		// 01
																			ENV_TOD_FLAGS_NIGHT,		// 02
																			ENV_TOD_FLAGS_NIGHT,		// 03
																			ENV_TOD_FLAGS_NIGHT,		// 04
																			ENV_TOD_FLAGS_DAWN,			// 05
																			ENV_TOD_FLAGS_DAWN,			// 06
																			ENV_TOD_FLAGS_DAWN,			// 07
																			ENV_TOD_FLAGS_DAY,		// 08
																			ENV_TOD_FLAGS_DAY,		// 09
																			ENV_TOD_FLAGS_DAY,		// 10
																			ENV_TOD_FLAGS_DAY,		// 11
																			ENV_TOD_FLAGS_DAY,			// 12
																			ENV_TOD_FLAGS_DAY,		// 13
																			ENV_TOD_FLAGS_DAY,			// 14
																			ENV_TOD_FLAGS_DAY,			// 15
																			ENV_TOD_FLAGS_DAY,			// 16
																			ENV_TOD_FLAGS_DAY,			// 17
																			ENV_TOD_FLAGS_DAY,			// 18
																			ENV_TOD_FLAGS_DUSK,			// 19
																			ENV_TOD_FLAGS_DUSK,			// 20
																			ENV_TOD_FLAGS_DUSK,			// 21
																			ENV_TOD_FLAGS_NIGHT,		// 22
																			ENV_TOD_FLAGS_NIGHT};		// 23

typedef enum
{
	COOL,
	WARM,
	HOT
} Temperatures;

typedef enum
{
	TEMPERATURE_DESERT_COOL,
	TEMPERATURE_DESERT_WARM,
	TEMPERATURE_DESERT_HOT,
	TEMPERATURE_GLOBAL_COOL,
	TEMPERATURE_GLOBAL_WARM,
	TEMPERATURE_GLOBAL_HOT,
} TemperatureEvents;

#define DESERT_WARM_START		( 8 * 60 )
#define DESERT_HOT_START		( 9 * 60 )
#define DESERT_HOT_END			(17 * 60 )
#define DESERT_WARM_END			(19 * 60 )

#define GLOBAL_WARM_START		( 9 * 60 )
#define GLOBAL_HOT_START		(12 * 60 )
#define GLOBAL_HOT_END			(14 * 60 )
#define GLOBAL_WARM_END			(17 * 60 )

#define HOT_DAY_LIGHTLEVEL 2

BOOLEAN		fTimeOfDayControls=TRUE;
UINT32		guiEnvTime=0;
UINT32		guiEnvDay=0;
UINT8			gubEnvLightValue = 0;
BOOLEAN		gfDoLighting		= FALSE;

UINT8		gubDesertTemperature = 0;
UINT8		gubGlobalTemperature = 0;

//rain
//extern BOOLEAN gfAllowRain;
//end rain

// local prototypes
void EnvDoLightning(void);


// polled by the game to handle time/atmosphere changes from gamescreen
void EnvironmentController( BOOLEAN fCheckForLights )
{
	UINT32			uiOldWorldHour;
	UINT8				ubLightAdjustFromWeather = 0;


	// do none of this stuff in the basement or caves
	if( gfBasement || gfCaves )
	{
	guiEnvWeather	&= (~WEATHER_FORECAST_THUNDERSHOWERS );
	guiEnvWeather	&= (~WEATHER_FORECAST_SHOWERS );

		if (gGameSettings.fOptions[ TOPTION_RAIN_SOUND ] == TRUE)
		{
			if ( guiRainLoop != NO_SAMPLE )
			{
				SoundStop( guiRainLoop );
				guiRainLoop = NO_SAMPLE;
			}
		}
		return;
	}

	if(fTimeOfDayControls )
	{
		uiOldWorldHour = GetWorldHour();

		// If hour is different
		if ( uiOldWorldHour != guiEnvTime )
		{
			// Hour change....

			guiEnvTime=uiOldWorldHour;
		}

		//ExecuteStrategicEventsUntilTimeStamp( (UINT16)GetWorldTotalMin( ) );

		// Polled weather stuff...
		// ONly do indooors
		if( !gfBasement && !gfCaves )
		{
//#if 0 //rain
			if ( guiEnvWeather & ( WEATHER_FORECAST_THUNDERSHOWERS | WEATHER_FORECAST_SHOWERS ) )
			{

				if (gGameSettings.fOptions[ TOPTION_RAIN_SOUND ] == TRUE)
				{
					if ( guiRainLoop == NO_SAMPLE )
					{
						if (guiEnvWeather & WEATHER_FORECAST_THUNDERSHOWERS )
						{
							guiRainLoop	= PlayJA2Ambient( RAIN_1, 140, 0 );
						}
						else
						{
							guiRainLoop	= PlayJA2Ambient( RAIN_1, 70, 0 );
						}
					}
				}

				// Do lightning if we want...
				if ( guiEnvWeather & ( WEATHER_FORECAST_THUNDERSHOWERS ) )
				{
					EnvDoLightning( );
				}

			}
			else
			{
				if (gGameSettings.fOptions[ TOPTION_RAIN_SOUND ] == TRUE)
				{
					if ( guiRainLoop != NO_SAMPLE )
					{
						SoundStop( guiRainLoop );
						guiRainLoop = NO_SAMPLE;
					}
				}
			}
//#endif //rain
		}

		if ( gfDoLighting && fCheckForLights )
		{
			// Adjust light level based on weather...
			ubLightAdjustFromWeather = GetTimeOfDayAmbientLightLevel();

			// ONly do indooors
			if( !gfBasement && !gfCaves )
			{
				// Rain storms....
//#if 0 //rain
				if ( guiEnvWeather & ( WEATHER_FORECAST_THUNDERSHOWERS | WEATHER_FORECAST_SHOWERS ) )
				{
					// Thunder showers.. make darker
					if ( guiEnvWeather & ( WEATHER_FORECAST_THUNDERSHOWERS ) )
					{
						ubLightAdjustFromWeather = (UINT8)(__min( gubEnvLightValue+2, NORMAL_LIGHTLEVEL_NIGHT ));
					}
					else
					{
						ubLightAdjustFromWeather = (UINT8)(__min( gubEnvLightValue+1, NORMAL_LIGHTLEVEL_NIGHT ));
					}
				}
//#endif //rain
			}


			LightSetBaseLevel( ubLightAdjustFromWeather );

			//Update Merc Lights since the above function modifies it.
			HandlePlayerTogglingLightEffects( FALSE );

			// Make teams look for all
			// AllTeamsLookForAll( FALSE );

			// Set global light value
			SetRenderFlags(RENDER_FLAG_FULL);
			gfDoLighting = FALSE;
		}

	}

}

void BuildDayLightLevels()
{
	UINT32 uiLoop, uiHour;

	/*
	// Dawn; light 12
	AddEveryDayStrategicEvent( EVENT_CHANGELIGHTVAL, DAWNLIGHT_START, NORMAL_LIGHTLEVEL_NIGHT - 1 );

	// loop from light 12 down to light 4
	for (uiLoop = 1; uiLoop < 8; uiLoop++)
	{
		AddEveryDayStrategicEvent( EVENT_CHANGELIGHTVAL, DAWN_START + 15 * uiLoop,	NORMAL_LIGHTLEVEL_NIGHT - 1 - uiLoop );
	}
	*/

	//Transition from night to day
	for( uiLoop = 0; uiLoop < 9; uiLoop++ )
	{
		AddEveryDayStrategicEvent( EVENT_CHANGELIGHTVAL, DAWN_START + 2 * uiLoop,	NORMAL_LIGHTLEVEL_NIGHT - 1 - uiLoop );
	}

	// Add events for hot times
	AddEveryDayStrategicEvent( EVENT_TEMPERATURE_UPDATE, DESERT_WARM_START, TEMPERATURE_DESERT_WARM );
	AddEveryDayStrategicEvent( EVENT_TEMPERATURE_UPDATE, DESERT_HOT_START, TEMPERATURE_DESERT_HOT );
	AddEveryDayStrategicEvent( EVENT_TEMPERATURE_UPDATE, DESERT_HOT_END, TEMPERATURE_DESERT_WARM );
	AddEveryDayStrategicEvent( EVENT_TEMPERATURE_UPDATE, DESERT_WARM_END, TEMPERATURE_DESERT_COOL );

	AddEveryDayStrategicEvent( EVENT_TEMPERATURE_UPDATE, GLOBAL_WARM_START, TEMPERATURE_GLOBAL_WARM );
	AddEveryDayStrategicEvent( EVENT_TEMPERATURE_UPDATE, GLOBAL_HOT_START, TEMPERATURE_GLOBAL_HOT );
	AddEveryDayStrategicEvent( EVENT_TEMPERATURE_UPDATE, GLOBAL_HOT_END, TEMPERATURE_GLOBAL_WARM );
	AddEveryDayStrategicEvent( EVENT_TEMPERATURE_UPDATE, GLOBAL_WARM_END, TEMPERATURE_GLOBAL_COOL );

/*
	// Twilight; light 5
	AddEveryDayStrategicEvent( EVENT_CHANGELIGHTVAL, TWILLIGHT_START, NORMAL_LIGHTLEVEL_DAY + 1 );

	// Dusk; loop from light 5 up to 12
	for (uiLoop = 1; uiLoop < 8; uiLoop++)
	{
		AddEveryDayStrategicEvent( EVENT_CHANGELIGHTVAL, DUSK_START + 15 * uiLoop, NORMAL_LIGHTLEVEL_DAY + 1 + uiLoop );
	}
*/

	//Transition from day to night
	for( uiLoop = 0; uiLoop < 9; uiLoop++ )
	{
		AddEveryDayStrategicEvent( EVENT_CHANGELIGHTVAL, DUSK_START + 2 * uiLoop,	NORMAL_LIGHTLEVEL_DAY + 1 + uiLoop );
	}

	//Set up the scheduling for turning lights on and off based on the various types.
	uiHour = NIGHT_TIME_LIGHT_START_HOUR == 24 ? 0 : NIGHT_TIME_LIGHT_START_HOUR;
	AddEveryDayStrategicEvent( EVENT_TURN_ON_NIGHT_LIGHTS, uiHour * 60, 0 );
	uiHour = NIGHT_TIME_LIGHT_END_HOUR == 24 ? 0 : NIGHT_TIME_LIGHT_END_HOUR;
	AddEveryDayStrategicEvent( EVENT_TURN_OFF_NIGHT_LIGHTS, uiHour * 60, 0 );
	uiHour = PRIME_TIME_LIGHT_START_HOUR == 24 ? 0 : PRIME_TIME_LIGHT_START_HOUR;
	AddEveryDayStrategicEvent( EVENT_TURN_ON_PRIME_LIGHTS, uiHour * 60, 0 );
	uiHour = PRIME_TIME_LIGHT_END_HOUR == 24 ? 0 : PRIME_TIME_LIGHT_END_HOUR;
	AddEveryDayStrategicEvent( EVENT_TURN_OFF_PRIME_LIGHTS, uiHour * 60, 0 );
}

void BuildDayAmbientSounds( )
{
	INT32									cnt;

	// Add events!
	for ( cnt = 0; cnt < gsNumAmbData; cnt++ )
	{
		switch( gAmbData[ cnt ].ubTimeCatagory )
		{
			case AMB_TOD_DAWN:
				AddSameDayRangedStrategicEvent( EVENT_AMBIENT, DAWN_START, DAWN_TO_DAY, cnt );
				break;
			case AMB_TOD_DAY:
				AddSameDayRangedStrategicEvent( EVENT_AMBIENT, DAY_START, DAY_TO_DUSK, cnt );
				break;
			case AMB_TOD_DUSK:
				AddSameDayRangedStrategicEvent( EVENT_AMBIENT, DUSK_START, DUSK_TO_NIGHT, cnt );
				break;
			case AMB_TOD_NIGHT:
				AddSameDayRangedStrategicEvent( EVENT_AMBIENT, NIGHT_START, NIGHT_TO_DAWN, cnt );
				break;
		}

	}

	//guiRainLoop = NO_SAMPLE;

	//rain
	if (gGameSettings.fOptions[ TOPTION_RAIN_SOUND ] == TRUE)
	{
		if ( guiRainLoop != NO_SAMPLE )
		{
			SoundStop( guiRainLoop );
			guiRainLoop = NO_SAMPLE;
		}
	}
	//end rain
}

//extern UINT16 gusRainChancePerDay, gusRainMinLength, gusRainMaxLength; //rain


void ForecastDayEvents( )
{
	UINT32 uiOldDay;
	UINT32 uiStartTime, uiEndTime;
	UINT8	ubStormIntensity;
//	UINT32 cnt;

	// Get current day and see if different
	if ( ( uiOldDay = GetWorldDay() ) != guiEnvDay )
	{
		// It's a new day, forecast weather
		guiEnvDay = uiOldDay;

		// Set light level changes
		//BuildDayLightLevels();

		// Build ambient sound queues
		BuildDayAmbientSounds( );

		// Build weather....

		// ATE: Don't forecast if start of game...
		if ( guiEnvDay > 1 )
		{
			//rain
			if ( Random( 100 ) < gGameExternalOptions.gusRainChancePerDay )
			{
				// Add rain!
				// Between 6:00 and 10:00
				uiStartTime = (UINT32)( Random( 1440 - 1 - gGameExternalOptions.gusRainMaxLength	) );
				// Between 5 - 15 miniutes
				uiEndTime		= uiStartTime + ( gGameExternalOptions.gusRainMinLength + Random( gGameExternalOptions.gusRainMaxLength - gGameExternalOptions.gusRainMinLength ) );

				ubStormIntensity = 0;


				//Kaiden: making thunderstorms optional
				if (gGameExternalOptions.gfAllowLightning)
				{
					// Randomze for a storm!
					if ( Random( 10 ) < 5 )
					{
						ubStormIntensity = 1;
					}
				}


				if( gGameExternalOptions.gfAllowRain ) AddSameDayRangedStrategicEvent( EVENT_RAINSTORM, uiStartTime, uiEndTime - uiStartTime, ubStormIntensity );

				//AddSameDayStrategicEvent( EVENT_BEGINRAINSTORM, uiStartTime, ubStormIntensity );
				//AddSameDayStrategicEvent( EVENT_ENDRAINSTORM,		uiEndTime, 0 );
			}
			//end rain


			/*
			// Should it rain...?
			if ( Random( 100 ) < 20 )
			{
				// Add rain!
				// Between 6:00 and 10:00
				uiStartTime = (UINT32)( 360 + Random( 1080 ) );
				// Between 5 - 15 miniutes
				uiEndTime		= uiStartTime + ( 5 + Random( 10 ) );

				ubStormIntensity = 0;

				// Randomze for a storm!
				if ( Random( 10 ) < 5 )
				{
					ubStormIntensity = 1;
				}

	// ATE: Disable RAIN!
	//			AddSameDayRangedStrategicEvent( EVENT_RAINSTORM, uiStartTime, uiEndTime - uiStartTime, ubStormIntensity );

				//AddSameDayStrategicEvent( EVENT_BEGINRAINSTORM, uiStartTime, ubStormIntensity );
				//AddSameDayStrategicEvent( EVENT_ENDRAINSTORM,		uiEndTime, 0 );
			}
			*/
		}
	}

}

void EnvEnableTOD(void)
{
	fTimeOfDayControls=TRUE;
}

void EnvDisableTOD(void)
{
	fTimeOfDayControls=FALSE;
}



//rain
UINT32 guiMinLightningInterval = 5;
UINT32 guiMaxLightningInterval = 15;

UINT32 guiMinDLInterval = 1;
UINT32 guiMaxDLInterval = 5;

UINT32 guiProlongLightningIfSeenSomeone = 5;
UINT32 guiChanceToDoLightningBetweenTurns = 20;


 // 60 = 1 second
#define MIN_LIGHTNING_INTERVAL ( 60 * guiMinLightningInterval )
#define MAX_LIGHTNING_INTERVAL ( 60 * guiMaxLightningInterval )

#define MAX_DELAYED_SOUNDS 10
#define NO_DL_SOUND 0xFFFFFFFF

// 1000 = 1 second
#define MIN_DL_INTERVAL ( 1000 * guiMinDLInterval )
#define MAX_DL_INTERVAL ( 1000 * guiMaxDLInterval )

#define EXTRA_ADD_VIS_DIST_IF_SEEN_SOMEONE ( 1000 * guiProlongLightningIfSeenSomeone	)
#define CHANCE_TO_DO_LIGHTNING_BETWEEN_TURNS guiChanceToDoLightningBetweenTurns

BOOLEAN gfLightningInProgress = FALSE;
BOOLEAN gfHaveSeenSomeone = FALSE;

UINT8 ubRealAmbientLightLevel = 0;
BOOLEAN gfTurnBasedDoLightning = FALSE;
BOOLEAN gfTurnBasedLightningEnd = FALSE;

BOOLEAN gfWasTurnBasedWhenLightningBegin = FALSE;

UINT8 gubLastTeamLightning;

#define IS_TURNBASED ( gTacticalStatus.uiFlags & TURNBASED &&	gTacticalStatus.uiFlags & INCOMBAT )

void BeginTeamTurn( UINT8 ubTeam );




void EnvDoLightning(void)
{
	static UINT32 uiCount=10, uiIndex=0, uiStrike=0, uiFrameNext=0;
	static UINT8 ubLevel=0, ubLastLevel=0;
	static UINT32 uiLastUpdate = 0xFFFFFFFF;
	static UINT32 uiTurnOffExtraVisDist = 0xFFFFFFFF;
	static UINT32 pDelayedSounds[ MAX_DELAYED_SOUNDS ];
	UINT32 uiDSIndex;

	if( GetJA2Clock() < uiLastUpdate )
	{
	uiLastUpdate = 0;
	memset( pDelayedSounds, NO_DL_SOUND, sizeof( UINT32 ) * MAX_DELAYED_SOUNDS );
	}

	if( GetJA2Clock() < uiLastUpdate + 1000 / 60 )return;
	else
		uiLastUpdate = GetJA2Clock();

	if( GetJA2Clock() > uiTurnOffExtraVisDist )
	{
	AllTeamsLookForAll( FALSE );
	uiTurnOffExtraVisDist = 0xFFFFFFFF;

	if( gfTurnBasedLightningEnd )
	{
		BeginTeamTurn( gubLastTeamLightning );
		gfTurnBasedLightningEnd = FALSE;
	}

	}

	for( uiDSIndex = 0; uiDSIndex < MAX_DELAYED_SOUNDS; ++uiDSIndex )
	if( GetJA2Clock() > pDelayedSounds[ uiDSIndex ] )
	{
		PlayJA2Ambient(LIGHTNING_1+Random(2), HIGHVOLUME, 1);
		pDelayedSounds[ uiDSIndex ] = NO_DL_SOUND;
	}

	if ( gfPauseDueToPlayerGamePause )
	{
	return;
	}

	if( IS_TURNBASED && !gfLightningInProgress )
	{
	if( !gfTurnBasedDoLightning )
	{
		return;
	}
	else
	{
		gfTurnBasedDoLightning = FALSE;
		uiFrameNext = 1;
		uiCount = 0;
		gfTurnBasedLightningEnd = TRUE;
	}
	}

	uiCount++;
	if(uiCount >= (uiFrameNext+10))
	{
		if( gfHaveSeenSomeone && gfWasTurnBasedWhenLightningBegin	)
			uiTurnOffExtraVisDist = GetJA2Clock() + EXTRA_ADD_VIS_DIST_IF_SEEN_SOMEONE;
		else
			uiTurnOffExtraVisDist = GetJA2Clock();

		gfLightningInProgress = FALSE;
		gfHaveSeenSomeone = FALSE;

		uiCount=0;
		uiIndex=0;
		ubLevel=0;
		ubLastLevel=0;

		uiStrike=Random(3);
		uiFrameNext=MIN_LIGHTNING_INTERVAL+Random(MAX_LIGHTNING_INTERVAL - MIN_LIGHTNING_INTERVAL);
	}
	else if(uiCount >= uiFrameNext)
	{
		if(uiCount == uiFrameNext)
		{
			//EnvStopCrickets();
//			PlayJA2Ambient(LIGHTNING_1+Random(2), HIGHVOLUME, 1);
			for( uiDSIndex = 0; uiDSIndex < MAX_DELAYED_SOUNDS; ++uiDSIndex )
				if( pDelayedSounds[ uiDSIndex ] == NO_DL_SOUND )
				{
					pDelayedSounds[ uiDSIndex ] = GetJA2Clock() + MIN_DL_INTERVAL+Random(MAX_DL_INTERVAL - MIN_DL_INTERVAL);
					break;
				}

			ubRealAmbientLightLevel = ubAmbientLightLevel;

			gfWasTurnBasedWhenLightningBegin = IS_TURNBASED;

			gfLightningInProgress = TRUE;
			AllTeamsLookForAll( FALSE );
		}

		while(uiCount > ((UINT32)ubLightningTable[uiStrike][uiIndex][0] + uiFrameNext))
			uiIndex++;

		ubLastLevel=ubLevel;
		ubLevel=min( ubRealAmbientLightLevel - 1, ubLightningTable[uiStrike][uiIndex][1] );

/*	// ATE: Don't modify if scrolling!
	if ( gfScrollPending || gfScrollInertia )
	{
	}
	else*/
	{
 		if(ubLastLevel!=ubLevel)
		{
			if(ubLevel > ubLastLevel)
			{
				LightAddBaseLevel(0, (UINT8)(ubLevel-ubLastLevel));
				if(ubLevel > 0)
					RenderSetShadows(TRUE);
			}
			else
			{
//				LightSubtractBaseLevel(0, (UINT8)(ubLastLevel-ubLevel));
				LightSetBaseLevel( ubRealAmbientLightLevel - ubLevel );
				if(ubLevel > 0)
					RenderSetShadows(TRUE);
			}
			SetRenderFlags(RENDER_FLAG_FULL);
		}
	}

	}
}

BOOLEAN LightningEndOfTurn( UINT8 ubTeam )
{
	if( !(guiEnvWeather & WEATHER_FORECAST_THUNDERSHOWERS) )return TRUE;
	if( Random(100) >= CHANCE_TO_DO_LIGHTNING_BETWEEN_TURNS ) return TRUE;

	if( !gfTurnBasedLightningEnd )
	{
		gfTurnBasedDoLightning = TRUE;
		gubLastTeamLightning = ubTeam;
		EnvDoLightning();
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

UINT8 GetTimeOfDayAmbientLightLevel()
{
	if (!is_networked)
	{
		if ( SectorTemperature( GetWorldMinutesInDay(), gWorldSectorX, gWorldSectorY, gbWorldSectorZ ) == HOT )
		{
			return( HOT_DAY_LIGHTLEVEL );
		}
		else
		{
			return( gubEnvLightValue );
		}
	}
	else
	{
		return ( gubEnvLightValue );
	}
}


void EnvBeginRainStorm( UINT8 ubIntensity )
{
	if( !gfBasement && !gfCaves )
	{
		gfDoLighting = TRUE;

		#ifdef JA2TESTVERSION
		ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_TESTVERSION, L"Starting Rain...."	);
		#endif

		// First turn off whatever rain it is, then turn on the requested rain
		guiEnvWeather &= ~(WEATHER_FORECAST_THUNDERSHOWERS | WEATHER_FORECAST_SHOWERS);

		if ( ubIntensity == 1 )
		{
			// Turn on rain storms
			guiEnvWeather	|= WEATHER_FORECAST_THUNDERSHOWERS;

			ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, New113Message[MSG113_STORM_STARTED] );
		}
		else
		{
			guiEnvWeather	|= WEATHER_FORECAST_SHOWERS;

			ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, New113Message[MSG113_RAIN_STARTED] );
		}
	}

}

void EnvEndRainStorm( )
{
	gfDoLighting = TRUE;

#ifdef JA2TESTVERSION
	ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_TESTVERSION, L"Ending Rain...."	);
#endif

	if ( guiEnvWeather & WEATHER_FORECAST_THUNDERSHOWERS )
	{
		  ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, New113Message[MSG113_STORM_ENDED] );
	}
	else
	{
  		  ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, New113Message[MSG113_RAIN_ENDED] );
	}


	guiEnvWeather	&= (~WEATHER_FORECAST_THUNDERSHOWERS );
	guiEnvWeather	&= (~WEATHER_FORECAST_SHOWERS );
}

//end rain









/*
void EnvDoLightning(void)
{
static UINT32 uiCount=0, uiIndex=0, uiStrike=0, uiFrameNext=1000;
static UINT8 ubLevel=0, ubLastLevel=0;

	if ( gfPauseDueToPlayerGamePause )
	{
	return;
	}

	uiCount++;
	if(uiCount >= (uiFrameNext+10))
	{
		uiCount=0;
		uiIndex=0;
		ubLevel=0;
		ubLastLevel=0;

		uiStrike=Random(3);
		uiFrameNext=1000+Random(1000);
	}
	else if(uiCount >= uiFrameNext)
	{
		if(uiCount == uiFrameNext)
		{
			//EnvStopCrickets();
			PlayJA2Ambient(LIGHTNING_1+Random(2), HIGHVOLUME, 1);
		}

		while(uiCount > ((UINT32)ubLightningTable[uiStrike][uiIndex][0] + uiFrameNext))
			uiIndex++;

		ubLastLevel=ubLevel;
		ubLevel=ubLightningTable[uiStrike][uiIndex][1];

	// ATE: Don't modify if scrolling!
	if ( gfScrollPending || gfScrollInertia )
	{
	}
	else
	{
 		if(ubLastLevel!=ubLevel)
		{
			if(ubLevel > ubLastLevel)
			{
				LightAddBaseLevel(0, (UINT8)(ubLevel-ubLastLevel));
				if(ubLevel > 0)
					RenderSetShadows(TRUE);
			}
			else
			{
				LightSubtractBaseLevel(0, (UINT8)(ubLastLevel-ubLevel));
				if(ubLevel > 0)
					RenderSetShadows(TRUE);
			}
			SetRenderFlags(RENDER_FLAG_FULL);
		}
	}
	}
}


UINT8 GetTimeOfDayAmbientLightLevel()
{
	if ( SectorTemperature( GetWorldMinutesInDay(), gWorldSectorX, gWorldSectorY, gbWorldSectorZ ) == HOT )
	{
		return( HOT_DAY_LIGHTLEVEL );
	}
	else
	{
		return( gubEnvLightValue );
	}
}


void EnvBeginRainStorm( UINT8 ubIntensity )
{
	if( !gfBasement && !gfCaves )
	{
		gfDoLighting = TRUE;

	#ifdef JA2TESTVERSION
	ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_TESTVERSION, L"Starting Rain...."	);
	#endif

	if ( ubIntensity == 1 )
	{
		// Turn on rain storms
		guiEnvWeather	|= WEATHER_FORECAST_THUNDERSHOWERS;
	}
	else
	{
		guiEnvWeather	|= WEATHER_FORECAST_SHOWERS;
	}
	}

}

void EnvEndRainStorm( )
{
	gfDoLighting = TRUE;

#ifdef JA2TESTVERSION
	ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_TESTVERSION, L"Ending Rain...."	);
#endif

	guiEnvWeather	&= (~WEATHER_FORECAST_THUNDERSHOWERS );
	guiEnvWeather	&= (~WEATHER_FORECAST_SHOWERS );
}
*/


void TurnOnNightLights()
{
	INT32 i;
	for( i = 0; i < MAX_LIGHT_SPRITES; i++ )
	{
		if( LightSprites[ i ].uiFlags & LIGHT_SPR_ACTIVE &&
			LightSprites[ i ].uiFlags & LIGHT_NIGHTTIME &&
				!(LightSprites[ i ].uiFlags & (LIGHT_SPR_ON|MERC_LIGHT) ) )
		{
			LightSpritePower( i, TRUE );
		}
	}
}

void TurnOffNightLights()
{
	INT32 i;
	for( i = 0; i < MAX_LIGHT_SPRITES; i++ )
	{
		if( LightSprites[ i ].uiFlags & LIGHT_SPR_ACTIVE &&
			LightSprites[ i ].uiFlags & LIGHT_NIGHTTIME &&
				LightSprites[ i ].uiFlags & LIGHT_SPR_ON &&
				!(LightSprites[ i ].uiFlags & MERC_LIGHT) )
		{
			LightSpritePower( i, FALSE );
		}
	}
}

void TurnOnPrimeLights()
{
	INT32 i;
	for( i = 0; i < MAX_LIGHT_SPRITES; i++ )
	{
		if( LightSprites[ i ].uiFlags & LIGHT_SPR_ACTIVE &&
			LightSprites[ i ].uiFlags & LIGHT_PRIMETIME &&
				!(LightSprites[ i ].uiFlags & (LIGHT_SPR_ON|MERC_LIGHT) ) )
		{
			LightSpritePower( i, TRUE );
		}
	}
}

void TurnOffPrimeLights()
{
	INT32 i;
	for( i = 0; i < MAX_LIGHT_SPRITES; i++ )
	{
		if( LightSprites[ i ].uiFlags & LIGHT_SPR_ACTIVE &&
			LightSprites[ i ].uiFlags & LIGHT_PRIMETIME &&
				LightSprites[ i ].uiFlags & LIGHT_SPR_ON &&
				!(LightSprites[ i ].uiFlags & MERC_LIGHT) )
		{
			LightSpritePower( i, FALSE );
		}
	}
}

void UpdateTemperature( UINT8 ubTemperatureCode )
{
	switch( ubTemperatureCode )
	{
		case TEMPERATURE_DESERT_COOL:
			gubDesertTemperature = 0;
			break;
		case TEMPERATURE_DESERT_WARM:
			gubDesertTemperature = 1;
			break;
		case TEMPERATURE_DESERT_HOT:
			gubDesertTemperature = 2;
			break;
		case TEMPERATURE_GLOBAL_COOL:
			gubGlobalTemperature = 0;
			break;
		case TEMPERATURE_GLOBAL_WARM:
			gubGlobalTemperature = 1;
			break;
		case TEMPERATURE_GLOBAL_HOT:
			gubGlobalTemperature = 2;
			break;
	}
	gfDoLighting = TRUE;
}

INT8 SectorTemperature( UINT32 uiTime, INT16 sSectorX, INT16 sSectorY, INT8 bSectorZ )
{
	// SANDRO - updated this code
	if (bSectorZ > 0)
	{
		// cool underground
		return( 0 );
	}
	else if ( IsSectorDesert( sSectorX, sSectorY ) && !( guiEnvWeather & ( WEATHER_FORECAST_SHOWERS | WEATHER_FORECAST_THUNDERSHOWERS ) ) ) // is desert
	{
		return( gubDesertTemperature );
	}
	else
	{
		return( gubGlobalTemperature );
	}
}
