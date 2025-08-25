#include "UPGamePlayTags.h"

namespace UPGamePlayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Cooldown, "Ability.Cooldown",
	                               "Ability is on cooldown and cannot be activated.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Move, "InputTag.Move", "Move input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Attack, "InputTag.Attack", "Attack input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Look, "InputTag.Look", "Look (mouse) input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Run, "InputTag.Run", "Run input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Dodge, "InputTag.Dodge", "Dodge input.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Event_ComboWindowOpen, "Event.ComboWindowOpen",
	                               "Event triggered when a combo window opens, allowing for combo attacks.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Event_ComboWindowEnd, "Event.ComboWindowEnd",
	                               "Event triggered when a combo window ends, preventing further combo attacks.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Player_ComboWindow, "Player.ComboWindow",
	                               "Player's combo window state, indicating whether a combo is currently active.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Player_Attack_1, "Player.Attack.1",
	                               "Player's first attack in a combo sequence, used to trigger combo attacks.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Player_Attack_2, "Player.Attack.2",
							   "Player's second attack in a combo sequence, used to trigger combo attacks.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Player_Attack_3, "Player.Attack.3",
							   "Player's third attack in a combo sequence, used to trigger combo attacks.");
	FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString)
	{
		const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
		FGameplayTag Tag = Manager.RequestGameplayTag(FName(*TagString), false);

		if (!Tag.IsValid() && bMatchPartialString)
		{
			FGameplayTagContainer AllTags;
			Manager.RequestAllGameplayTags(AllTags, true);

			for (const FGameplayTag& TestTag : AllTags)
			{
				if (TestTag.ToString().Contains(TagString))
				{
					UE_LOG(LogTemp, Display,
					       TEXT("Could not find exact match for tag [%s] but found partial match on tag [%s]."),
					       *TagString, *TestTag.ToString());
					Tag = TestTag;
					break;
				}
			}
		}

		return Tag;
	}
}
