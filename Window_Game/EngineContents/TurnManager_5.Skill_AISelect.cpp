#include "PreCompile.h"
#include "TurnManager.h"

#include "Pokemon.h"
#include "Player.h"



bool SortFuncD(APokemon* first, APokemon* second) {
	return first->GetSPD() > second->GetSPD();
}

void ATurnManager::Skill_AISelect()
{
	// speed로 정렬
	AllAIPokemon.sort(SortFuncD);
	PlayerCamp.sort(SortFuncD);
	EnemyCamp.sort(SortFuncD);

	//	모든 AI포켓몬들
	for (APokemon* CurPokemon : AllAIPokemon) {
		bool IsFindTarget = false;
		CurPokemon->ResetCurDuration();
		CurPokemon->ClearTargetablePokemon();
		FIntPoint CurTile = CurPokemon->GetTile();
		CampType CurPokemonCamp = CurPokemon->GetCamp();
		//	반대진영 리스트가져옴
		std::list<APokemon*>& CompareCamp = (CurPokemonCamp == CampType::Player) ? EnemyCamp : PlayerCamp;
		// 타켓로케이션 확인
		for (APokemon* CurComparePokemon : CompareCamp) {
			FIntPoint CompareTile = CurComparePokemon->GetTargetTile();
			FIntPoint Distance = CompareTile - CurTile;
			//	근처에 적이 있다면 스킬리스트
			if (std::abs(Distance.X) <= 1 && std::abs(Distance.Y) <= 1) {
				IsFindTarget = true;
				break;
			}
		}
		if (IsFindTarget) {
			SkillPokemon.push_back(CurPokemon);
		}
		//	근처에 적이 없다면 무브리스트
		else if (!IsFindTarget) {
			//	플레이어를 향해 길찾기
			FIntPoint PlayerTile = Player->GetTargetTile();
			std::list<FIntPoint> PathForPlayer = PathFinder.PathFind(CurTile, PlayerTile);
			if (!PathForPlayer.empty()) {
				auto Path = PathForPlayer.begin();
				if (++Path == PathForPlayer.end()) {
					Path = PathForPlayer.begin();
				}
				CurPokemon->SetTargetTile(*Path);
				MovePokemon.push_back(CurPokemon);
			}
		}
	}

	// 최종체크 - 서로서로 안겹치게 조정
	for (APokemon* CurPokemon : MovePokemon) {
		bool IsStand = false;
		FIntPoint CurTarget = CurPokemon->GetTargetTile();
		for (APokemon* ComparePokemon : MovePokemon) {
			if (ComparePokemon == CurPokemon) {
				break;
			}
			// 무브리스트 중 자신보다 스피드 빠른 포켓몬이랑 타겟로케이션 겹치면 제자리
			if (CurTarget == ComparePokemon->GetTargetTile()) {
				CurPokemon->SetTargetLocation(CurPokemon->GetActorLocation());
				IsStand = true;
				break;
			}
		}
		// 위에 조건에 안걸렸다면 스킬리스트 중 겹치는지 확인
		if (!IsStand) {
			for (APokemon* ComparePokemon : SkillPokemon) {
				if (CurTarget == ComparePokemon->GetTargetTile()) {
					CurPokemon->SetTargetLocation(CurPokemon->GetActorLocation());
					IsStand = true;
					break;
				}
			}
		}
		// 문제없다면 방향설정
		if (!IsStand) {
			FVector2D Dir = (CurPokemon->GetTargetLocation() - CurPokemon->GetActorLocation()) / 72.0f;
			if (Dir != FVector2D::ZERO) {
				CurPokemon->SetDir(UContentsMath::FVector2D_To_DIR(Dir));
			}
		}
	}


	CurTurn = TurnType::AI_Move_Start;
	return;
}