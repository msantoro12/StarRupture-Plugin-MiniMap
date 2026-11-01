#pragma once

#include "SDK/Engine_classes.hpp"
#include "SDK/Chimera_classes.hpp"
#include "SDK/Chimera_structs.hpp"
#include <plugin_interface.h>
#include <plugin_map.h>

#include <cstdint>
#include <vector>

// The map keys of the game functions and the members of game classes MiniMap
// uses, as the loader sees them for the running game build (see plugin_map.h).
// The functions are requested in MiniMapFingerprints::Resolve, the members in
// MiniMapFields::Resolve; both run in OnPluginLoadHooks after the features
// below are declared, so a miss turns off the layer it belongs to and not the
// plugin. Engine layout MiniMap keeps compiled is listed in the README.

namespace MiniMapFields
{
	// The map keys of the game functions MiniMap resolves, so the resolves and
	// the feature declarations spell each one once. A key of a CODE or
	// IN_FUNCTION request is a site the loader reads as "MiniMap/<key>".
	namespace Keys
	{
		// The player's pose and the objects every layer reads
		inline constexpr const char* CommonUIActivated   = "UCommonActivatableWidget::NativeOnActivated";
		inline constexpr const char* CommonUIDeactivated = "UCommonActivatableWidget::NativeOnDeactivated";
		inline constexpr const char* FirstPlayerController = "UWorld::GetFirstPlayerController";
		inline constexpr const char* ComponentLocation   = "USceneComponent::K2_GetComponentLocation";
		inline constexpr const char* ControlRotation     = "AController::GetControlRotation";
		inline constexpr const char* InForgottenEngine   = "ACrCharacterPlayerBase::IsPlayerInForgottenEngine";
		inline constexpr const char* GameThread          = "IsInGameThread";
		inline constexpr const char* RetainObject        = "UObject::AddRef";
		inline constexpr const char* ReleaseObject       = "UObject::ReleaseRef";
		inline constexpr const char* NameEqualsWide      = "FName::EqualsWide";
		inline constexpr const char* ObjectArray         = "GUObjectArray (anchor)";

		// Textures and the terrain
		inline constexpr const char* LoadSynchronous     = "FSoftObjectPtr::LoadSynchronous";
		inline constexpr const char* BrushTexture        = "UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D";
		inline constexpr const char* ForceMips           = "UStreamableRenderAsset::SetForceMipLevelsToBeResident";
		inline constexpr const char* WaitForStreaming    = "UStreamableRenderAsset::WaitForStreaming";
		inline constexpr const char* ResidentMips        = "UTexture2D::GetNumResidentMips";
		inline constexpr const char* AllowedMips         = "UTexture2D::GetNumMipsAllowed";
		inline constexpr const char* NumMips             = "UTexture2D::GetNumMips";
		inline constexpr const char* StreamIn            = "UTexture2D::StreamIn";
		inline constexpr const char* WaitForPendingInit  = "UStreamableRenderAsset::WaitForPendingInitOrStreaming";
		inline constexpr const char* PlatformData        = "UTexture2D::GetPlatformData";
		inline constexpr const char* BulkDataSize        = "FBulkData::GetBulkDataSize";
		inline constexpr const char* CanLoadFromDisk     = "FBulkData::CanLoadFromDisk";
		inline constexpr const char* BulkDataCopy        = "FBulkData::GetCopy";
		inline constexpr const char* MemoryFree          = "FMemory::Free";

		// Points of interest and foundables
		inline constexpr const char* GetAllActorsOfClass = "UGameplayStatics::GetAllActorsOfClass";
		inline constexpr const char* PoiStaticClass      = "ACrPointOfInterestMarkerActor::StaticClass";
		inline constexpr const char* PoiCategory         = "UCrMapMenuDevSettings::FindPOIMarkerCategoryData";
		inline constexpr const char* MarkerFilter        = "UCrPlayerMapMenuDataComponent::GetMapMenuMarkerFiltersOnOffStatus";
		inline constexpr const char* AbandonBaseCompleted = "FCrAbandonBaseData::IsCompleted";
		inline constexpr const char* FoundableCategory   = "UCrMapMenuDevSettings::FindFoundableMarkerCateroryData";

		// Mass entity queries
		inline constexpr const char* MassSubsystem       = "UWorld::GetSubsystem<UMassEntitySubsystem>";
		inline constexpr const char* QueryConstruct      = "FMassEntityQuery::FMassEntityQuery";
		inline constexpr const char* QueryDestruct       = "FMassEntityQuery::~FMassEntityQuery";
		inline constexpr const char* MatchingHandles     = "FMassEntityQuery::GetMatchingEntityHandles";
		inline constexpr const char* AddInventoryRequirement = "FMassFragmentRequirements::AddRequirement<FCrInventoryFragment>";
		inline constexpr const char* AddTransformRequirement = "FMassFragmentRequirements::AddRequirement<FTransformFragment>";
		inline constexpr const char* AddEnemyStateRequirement = "FMassFragmentRequirements::AddRequirement<FMassEnemyStateFragment>";
		inline constexpr const char* AddFoundableParameters = "FMassFragmentRequirements::AddConstSharedRequirement<FCrMassFoundableParameters>";
		inline constexpr const char* AddFoundableTag     = "FMassFragmentRequirements::AddTagRequirement<FCrMassFoundableTag>";
		inline constexpr const char* AddTagRequirement   = "FMassFragmentRequirements::AddTagRequirement";
		inline constexpr const char* FragmentDataPtr     = "FMassEntityManager::InternalGetFragmentDataPtr";
		inline constexpr const char* ConstSharedPtr      = "FMassEntityManager::InternalGetConstSharedFragmentPtr";
		inline constexpr const char* IsEntityBuilt       = "FMassEntityManager::IsEntityBuilt";
		inline constexpr const char* IsEntityValid       = "FMassEntityManager::IsEntityValid";
		inline constexpr const char* TransformStaticStruct = "FTransformFragment::StaticStruct";
		inline constexpr const char* InventoryStaticStruct = "FCrInventoryFragment::StaticStruct";
		inline constexpr const char* FoundableStaticStruct = "FCrMassFoundableParameters::StaticStruct";
		inline constexpr const char* EnemyStateStaticStruct = "FMassEnemyStateFragment::StaticStruct";
		inline constexpr const char* EnemyTagStaticStruct = "FMassEnemyTag::StaticStruct";
		inline constexpr const char* NeutralTagStaticStruct = "FMassNeutralAITag::StaticStruct";

		// Buildings: the entity grid and the spline payload
		inline constexpr const char* GridSubsystem       = "UWorld::GetSubsystem<UCrEntityGridSubsystem>";
		inline constexpr const char* GridForEachCell     = "UCrEntityGridSubsystem::ForEachCellInRadius";
		inline constexpr const char* SplinePayloadGet    = "SplinePayload::GetSplineActorData";
		inline constexpr const char* SplinePayloadDestroy = "FAuAPSplineActorPayloadData::~FAuAPSplineActorPayloadData";
		inline constexpr const char* SplinePayloadStaticStruct = "FAuAPSplineActorPayloadData::StaticStruct";

		// Building sprites: the private capture world, the render target and the readback
		inline constexpr const char* SpawnObject         = "StaticConstructObject (TSubclassOf)";
		inline constexpr const char* SetObjectFlags      = "UObjectBase::AtomicallySetFlags";
		inline constexpr const char* RegisterComponent   = "UActorComponent::RegisterComponentWithWorld";
		inline constexpr const char* UnregisterComponent = "UActorComponent::UnregisterComponent";
		inline constexpr const char* DestroyComponent    = "UActorComponent::DestroyComponent";
		inline constexpr const char* InitRenderTarget    = "UTextureRenderTarget2D::InitCustomFormat";
		inline constexpr const char* RenderTargetResource = "UTextureRenderTarget2D::GameThread_GetRenderTargetResource";
		inline constexpr const char* TransitionResources = "FRHIComputeCommandList::Transition";
		inline constexpr const char* FenceConstruct      = "FRenderCommandFence::FRenderCommandFence";
		inline constexpr const char* FenceDestroy        = "FRenderCommandFence::~FRenderCommandFence";
		inline constexpr const char* FenceBegin          = "FRenderCommandFence::BeginFence";
		inline constexpr const char* FencePoll           = "FRenderCommandFence::IsFenceComplete";
		inline constexpr const char* FromValidEName      = "FNameEntryId::FromValidEName";
		inline constexpr const char* SubmitRenderCommand = "EnqueueUniqueRenderCommand";
		inline constexpr const char* ImmediateCommandList = "FRHICommandListExecutor::GetImmediateCommandList";
		inline constexpr const char* CreateRHITexture    = "FDynamicRHI::RHICreateTexture";
		inline constexpr const char* ReadbackConstruct   = "FRHIGPUTextureReadback::FRHIGPUTextureReadback";
		inline constexpr const char* ReadbackDestroy     = "FRHIGPUTextureReadback::~FRHIGPUTextureReadback";
		inline constexpr const char* ReadbackCopy        = "FRHIGPUTextureReadback::EnqueueCopy";
		inline constexpr const char* ReadbackLock        = "FRHIGPUTextureReadback::Lock";
		inline constexpr const char* ReadbackUnlock      = "FRHIGPUTextureReadback::Unlock";
		inline constexpr const char* GpuFencePoll        = "FRHIGPUFence::Poll";
		inline constexpr const char* MarkForDelete       = "FRHIResource::MarkForDelete";
		inline constexpr const char* MemoryMalloc        = "FMemory::Malloc";
		inline constexpr const char* ReadbackFree        = "FMemory::Free (readback)";
		inline constexpr const char* DynamicRHI          = "GDynamicRHI (anchor)";
		inline constexpr const char* RenderCommandPipe   = "GRenderCommandPipe (anchor)";
		inline constexpr const char* ThreadedRendering   = "GIsThreadedRendering (anchor)";
		inline constexpr const char* RHIMultithreading   = "GRHISupportsRHIThread (anchor)";
		inline constexpr const char* GpuCount            = "GNumExplicitGPUsForRendering (anchor)";
		inline constexpr const char* CreateWorld         = "UWorld::CreateWorld";
		inline constexpr const char* InitWorld           = "UWorld::InitWorld";
		inline constexpr const char* UpdateWorldComponents = "UWorld::UpdateWorldComponents";
		inline constexpr const char* CleanupWorld        = "UWorld::CleanupWorld";
		inline constexpr const char* WorldContext        = "UEngine::GetWorldContextFromWorld";
		inline constexpr const char* GetSubsystemInternal = "FSubsystemCollectionBase::GetSubsystemInternal";
		inline constexpr const char* GarbageCollectingLocking = "IsGarbageCollectingAndLockingUObjectHashTables";
		inline constexpr const char* PurgePending        = "IsIncrementalPurgePending";
		inline constexpr const char* ReachabilityPending = "IsIncrementalReachabilityPending";
		inline constexpr const char* TickableTickType    = "FTickableGameObject::GetTickableTickType";
		inline constexpr const char* VisibilityPending   = "UWorld::IsVisibilityRequestPending";
		inline constexpr const char* DestroyActor        = "UWorld::DestroyActor";
		inline constexpr const char* ActiveGarbageCollection = "GIsGarbageCollecting (anchor)";
		inline constexpr const char* EngineStorage       = "GEngine (anchor)";
		inline constexpr const char* ReadbackGlobals     = "Readback globals (executable headers)";
		inline constexpr const char* ReleaseGuard        = "UObject::ReleaseRef (guard)";
	}

	// The player character and controller. Every layer starts from the player's
	// pose, so these are core: a miss refuses the plugin.
	inline auto PlayerMainCharacter = SR_FIELD(SDK::ACrCharacterPlayerBase*, ACrPlayerControllerBase, PlayerMainCharacter, 0);
	inline auto IsDead              = SR_FIELD(bool, ACrCharacterPlayerBase, bDead, 0);
	inline auto Status              = SR_FIELD(SDK::EPlayerCharacterStatus, ACrCharacterPlayerBase, Status, 0);
	inline auto BuildingDrone       = SR_FIELD(SDK::ACrCharacterDroneBase*, ACrCharacterPlayerBase, BuildingDrone, 0);
	inline auto DroneOwner          = SR_FIELD(SDK::ACrCharacterPlayerBase*, ACrCharacterDroneBase, OwnerPlayer, 0);

	// Asks the loader for every row above. False when any did not resolve; the
	// loader has then recorded the failure and refuses the plugin or turns off
	// the feature that lists it.
	inline bool Resolve(IPluginSelf* self, IPluginHookScanner* scanner)
	{
		return PluginMap::ResolveFields(scanner, self,
			PlayerMainCharacter, IsDead, Status, BuildingDrone, DroneOwner);
	}

	using PluginMap::KeysOf;

	// The layers that can be off while the rest runs. Each lists the keys only it
	// needs; a key two layers need is listed in both. The terrain is not one:
	// it gives every other layer its transform, so a miss there leaves nothing
	// to draw and refuses the plugin. Declared in OnPluginLoadHooks before any key
	// is resolved. Every entry point of a layer checks On(), so an off layer runs
	// nothing and reads none of its keys or config entries.
	namespace Features
	{
		inline PluginMap::Feature FogOfWar{ "fog-of-war", "Fog of war on the minimap",
			KeysOf(),
			{ "Fog Of War.DisableFog", "Fog Of War.FeatherRange" } };

		inline PluginMap::Feature PointsOfInterest{ "points-of-interest", "Points of interest on the minimap",
			KeysOf(Keys::GetAllActorsOfClass, Keys::PoiStaticClass, Keys::PoiCategory, Keys::MarkerFilter,
				Keys::AbandonBaseCompleted),
			{ "Points Of Interest.ShowLayer", "Points Of Interest.MarkerScale" } };

		inline PluginMap::Feature Foundables{ "foundables", "Foundables on the minimap",
			KeysOf(Keys::GetAllActorsOfClass, Keys::FoundableCategory, Keys::MarkerFilter,
				Keys::MassSubsystem, Keys::QueryConstruct, Keys::QueryDestruct, Keys::MatchingHandles,
				Keys::FragmentDataPtr, Keys::ConstSharedPtr, Keys::AddInventoryRequirement,
				Keys::AddTransformRequirement, Keys::AddFoundableParameters, Keys::AddFoundableTag,
				Keys::AddTagRequirement, Keys::TransformStaticStruct, Keys::InventoryStaticStruct,
				Keys::FoundableStaticStruct),
			{ "Foundables.ShowLayer", "Foundables.ShowLootInBases", "Foundables.MarkerScale" } };

		inline PluginMap::Feature AlienActors{ "alien-actors", "Alien actors on the minimap",
			KeysOf(Keys::MassSubsystem, Keys::QueryConstruct, Keys::QueryDestruct, Keys::MatchingHandles,
				Keys::FragmentDataPtr, Keys::AddTransformRequirement, Keys::AddEnemyStateRequirement,
				Keys::AddTagRequirement, Keys::TransformStaticStruct, Keys::EnemyStateStaticStruct,
				Keys::EnemyTagStaticStruct, Keys::NeutralTagStaticStruct),
			{ "Alien Actors.ShowLayer" } };

		inline PluginMap::Feature Buildings{ "buildings", "Buildings on the minimap",
			KeysOf(Keys::MassSubsystem, Keys::QueryConstruct, Keys::QueryDestruct, Keys::MatchingHandles,
				Keys::FragmentDataPtr, Keys::ConstSharedPtr, Keys::AddTransformRequirement,
				Keys::AddTagRequirement, Keys::IsEntityBuilt, Keys::IsEntityValid, Keys::GridSubsystem,
				Keys::GridForEachCell, Keys::SplinePayloadGet, Keys::SplinePayloadDestroy,
				Keys::SplinePayloadStaticStruct),
			{ "Buildings.ShowLayer", "Buildings.RenderDroneRails" } };

		inline PluginMap::Feature BuildingSprites{ "building-sprites", "Building pictures on the minimap",
			KeysOf(Keys::SpawnObject, Keys::SetObjectFlags, Keys::RegisterComponent, Keys::UnregisterComponent,
				Keys::DestroyComponent, Keys::InitRenderTarget, Keys::RenderTargetResource,
				Keys::TransitionResources, Keys::FenceConstruct, Keys::FenceDestroy, Keys::FenceBegin,
				Keys::FencePoll, Keys::FromValidEName, Keys::SubmitRenderCommand, Keys::ImmediateCommandList,
				Keys::CreateRHITexture, Keys::ReadbackConstruct, Keys::ReadbackDestroy, Keys::ReadbackCopy,
				Keys::ReadbackLock, Keys::ReadbackUnlock, Keys::GpuFencePoll, Keys::MarkForDelete,
				Keys::MemoryMalloc, Keys::ReadbackFree, Keys::DynamicRHI, Keys::RenderCommandPipe,
				Keys::ThreadedRendering, Keys::RHIMultithreading, Keys::GpuCount, Keys::ReadbackGlobals,
				Keys::ReleaseGuard, Keys::CreateWorld, Keys::InitWorld, Keys::UpdateWorldComponents,
				Keys::CleanupWorld, Keys::WorldContext, Keys::GetSubsystemInternal,
				Keys::GarbageCollectingLocking, Keys::PurgePending, Keys::ReachabilityPending,
				Keys::TickableTickType, Keys::VisibilityPending, Keys::DestroyActor,
				Keys::ActiveGarbageCollection, Keys::EngineStorage),
			{ "Buildings.CaptureSprites" } };

		// Declares every layer; call before any key is resolved.
		inline bool Declare(IPluginSelf* self, IPluginHookScanner* scanner)
		{
			return PluginMap::DeclareFeatures(scanner, self,
				FogOfWar, PointsOfInterest, Foundables, AlienActors, Buildings, BuildingSprites);
		}
	}
}
