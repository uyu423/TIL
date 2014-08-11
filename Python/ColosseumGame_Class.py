'''
Created on 2014. 8. 10.

@author: uyu423@gmail.com
'''

import random

class Player:
    
    def __init__(self, name):
        self.hp = 100
        self.name = name
        self.weapon = None
        
    def setWeapon(self, weapon):
        self.weapon = weapon    
        
    def Attack(self):
        return self.weapon.makeHitPoint()
    
    def Damage(self, amount):
        self.hp = self.hp - amount

    def __str__(self):  # Java의 toString
        return self.name + " HP : " + str(self.hp) + " // Weapon : " + str(self.weapon.name) + "("+str(self.weapon.def_dam)+"~"+str(self.weapon.max_dam)+")"  

class Weapon:
    
    def __init__(self, name, def_dam, max_dam):
        self.name = name
        self.def_dam = def_dam
        self.max_dam = max_dam
        
    def makeHitPoint(self):
        return random.randint(self.def_dam, self.max_dam)
        
class Colosseum:
    
    def __init__(self):
        self.weapons = []
        self.weapons.append(Weapon("Sword", 5, 5))
        self.weapons.append(Weapon("Sphere", 6, 9))
        self.weapons.append(Weapon("Axe", 1, 15))
        random.shuffle(self.weapons)
            
    def makePlayer(self):
        playerName = input("Player Name : ")
        return Player(playerName)
    
    def Battle(self):
        print("첫번째 플레이어 만들기")
        p1 = self.makePlayer()
        p1.setWeapon(self.weapons[0])
        print("두번째 플레이어 만들기")
        p2 = self.makePlayer()
        p2.setWeapon(self.weapons[1])
        
        while p1.hp > 0 or p2.hp > 0:
            print("--------------------")
            print(p1)
            print(p2)
            
            input("플레이어1이 공격할까요?")
            point = p1.Attack()
            p2.Damage(point)
            print("플레이어2에게 %d 데미지" % (point))
            
            if p1.hp <= 0:
                print("플레이어2이 이겼습니다.")
                return
            
            input("플레이어2가 공격할까요?")
            point = p2.Attack()
            p1.Damage(point)
            print("플레이어1에게 %d 데미지" % (point))
                
            if p2.hp <= 0:
                print("플레이어1이 이겼습니다.")
                return
        

def main():
    colosseum = Colosseum()
    colosseum.Battle()
    
    
if __name__ == '__main__':
    main() 
