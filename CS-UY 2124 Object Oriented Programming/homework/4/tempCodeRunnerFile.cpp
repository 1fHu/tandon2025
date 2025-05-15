          
          double finalArmyStrength = 0;
          double finalOpponentStrength = 0;

          for (Warrior* oneWarrior : army){
               finalArmyStrength += oneWarrior->getStrength();
          }
          for (Warrior* oneWarrior : opponent.army){
               finalOpponentStrength += oneWarrior->getStrength();
          }