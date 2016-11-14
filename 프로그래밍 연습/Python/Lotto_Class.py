'''
Created on 2014. 8. 10.

@author: uyu423@gmail.com
'''

import random

# 0. 객체지향을 통해 크게 3가지 형태의 클래스가 나온다. Data, B.O, U.I
# 1. 데이터를 클래스로 만들 수 있음(Data)
# 2. 프로그램이 해야하는 기능을 모아서 클래스로 만들 수 있음(Business Object(B.O). B.O는 입출력을 처리하지 않음(중요)
# 3. 실제 입출력을 담당하는 UI 클래스도 있음(UI)
# 4. 모든 프로그램은 CRUD(Create, Read, Update, Delete)가 기본

class LottoBall:  # Data 

    def __init__(self, num):
        self.num = num
        
class LottoMachine:  # B.O
    
    def __init__(self):
        self.ballList = []
        for i in range(1, 46):
            self.ballList.append(LottoBall(i))
            
    def selectBalls(self):
        random.shuffle(self.ballList)
        return self.ballList[0:6]
    
class LottoUI:  # U.I
    
    def __init__(self):
        self.machine = LottoMachine()
        
    def playLotto(self):
        input("로또를 뽑을까요?")
        selectedBalls = self.machine.selectBalls()
        for ball in selectedBalls:
            print("%d" % (ball.num))

# main
ui = LottoUI()
ui.playLotto()
