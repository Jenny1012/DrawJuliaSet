# DrawJuliaSet  
題目(final_project)  
  
108學年度第1學期  
   
一、背景  
本project的程式包含4個檔案：name.s、id.s、main.c以及drawJuliaSet.s，使四個檔案編譯後執行，可在視窗上看到Julia Set繪製的動畫。使用Midterm project所開發的Name、Id兩個組合語言函數，列印組別、組員名字、與學號。同時以ARM組合語言重新設計drawJuliaSet函數，並參考Project檔案中的main程式，進行修改。除了main.c之外，其餘的程式均需以ARM組合語言完成。  
  
1.	撰寫4個function：name.s，id.s，drawJuliaSet.s與main.c，並分成三個組合語言檔案：name.s,id.s,drawJuliaSet.s、與一個C語言檔案：main.c。  
2.	需以ARM組合語言重新撰寫Julia Set的函數：drawJuliaSet，並存放於drawJuliaSet.s的檔案裡。  
3.	使用Data Processing指令中，13種Operand2格式的當中4種以上。  
4.	程式中須包含2道以上不同的非Branch指令的Conditional Execution。(不包括AL或”不指定”條件)  
5.	在name.s程式中須包含一道一定要執行的指令：adds r15, r14, r13。  
6.	在drawJuliaSet.s中須包含一道一定要執行的指令：sub r0, r14, r13。  
  
二、方法  
1.	Name function ：  
  ![image](https://user-images.githubusercontent.com/64779422/193545429-7cf5b254-0fe0-4bf6-afcd-6cd769bbb3f9.png)
  ![image](https://user-images.githubusercontent.com/64779422/193545448-2528d575-eefb-4a3c-9d9f-3acdb8e46dfe.png)
  ![image](https://user-images.githubusercontent.com/64779422/193545466-d873cea3-fac5-4ba8-92d0-e332a09a3524.png)
  
首先，分別用6個不同的label來宣告提示字串、組別與組員名字(將組別名稱與組員名字設為global)，並在程式執行前先將r7、r8、r9、r10、linker register (r14)中的return address (中斷指令時的pc位址，作為返回的位址)備份儲存至stack pointer (r13)中，並將main最後一個參數的回傳位址存放進r4，再將組別名稱複製進去參數的位址。再依序修正main的參數位址(因為在宣告區域變數的時候，記憶體的stack區塊就會配位子給區域變數，所以愈早宣告的參數記憶體位址愈高)，因為愈早宣告的參數記憶體位址愈高，且ARM的stack為反敘，所以以r3(teamname，main回傳參數的最後一個)為基準位址，將組員名字複製進去參數位址，並且將參數位址依序加上12(因為每個宣告的char array組員名字大小為12)、回到前一個參數的位址(r2)，依此類推，依序複製完所有的組員名字進去回傳的參數位址。再將提示字串的位址中的值存放進r0、並且列印位址中所存的值；其次，將組別與組員的位址中的值存放進r5、r6、r7、r8，並分別將以上暫存器中的內容移入r0、並印出內容。
最後，備份在r7、r8、r9、r10、stack pointer(r13)中的return address還原給linker register(r14)，並將program counter(r15)設定成linker register(r14)，即可結束name function，回到main。  
  
2.	Id function ：  
  ![image](https://user-images.githubusercontent.com/64779422/193545502-ec058e6e-cf92-46dd-8e7a-346ee0c98664.png)
  ![image](https://user-images.githubusercontent.com/64779422/193545520-92b8b713-9909-47f9-b57a-b711ca66dab2.png)
  ![image](https://user-images.githubusercontent.com/64779422/193545544-4d1d9d28-fba2-4055-b5b5-49e7d64bd7da.png)
  ![image](https://user-images.githubusercontent.com/64779422/193545563-89bb3915-596e-4b2b-b6db-cf56949f511d.png)
  ![image](https://user-images.githubusercontent.com/64779422/193545573-df6db313-9565-4eb8-b994-00309c718a62.png)
  
首先，使用label來宣告程式所需要的字串和參數，並在程式執行前先將r4、r5、r6、linker register (r14)中的return address (中斷指令時的pc位址，作為返回的位址)備份儲存至stack pointer (r13)中。並將main第一個參數的回傳位址存放進r5，並將提示字串的位址中的值存放進r0、並且列印位址中所存的值，並將r4清空，作學號加總的計算。  
接著為輸入學號，設定r0為字串為所需字串(%d)，而r1為儲存學號位址，利用scanf將讀入的ID1內容存放進r1所在位址中。將r2設定為ID1所在位址，再將其位址內容提出設定回r2，故r2的值便成為了學號，將r2的內容存放入r5的位址中，並且將r4設定為r4+r2，便可計算學號總和。並依序讀完三個學號，並將其他兩個學號存在r5+4與r5+8的位址，最後將r6設定為sum總和的所在位址，並將r4中的總合存入r6的位址中，再將r6的位址提出設定回r6，故r6的值便成了學號的總和，再將r6中的學號總和存入r5+12的位址中。  
讀指令，首先須將先讀掉換行，讀的方法為將r0設定為所需字串(%d)的位址，而r1指令讀入的位址，進行scanf。再者為印出提示字串，最後才是讀取指令。接下來就需要判斷指令是否為P/p，就是先將r0設定為之前已經宣告p label的位址，將裡面的內容設定到r0中，而r1也跟r0一樣只是改成指令的位址及內容，故r0和r1分別都是內容，判斷其內容是否相等。若相等則執行印出所有學號以及總合，若不相等則比較是否為P，若不是則結束此function，若是則執行印出所有學號以及總和。  
印出所有學號以及總合，先將所需的提示字串印出，再來就需要印出學號，印出方法與先前相同，將r0設為字串(%d\n)的位址，再將r1依序設為ID1、ID2、ID3的內容，而ID1、ID2、ID3的內容分別在r5、r5+4、r5+8的位置中，然後印出。印出總和也相同，將r0設為提示字串的位址，將r1設為r6，並印出總和。最後，備份在r4、r5、r6、stack pointer(r13)中的return address還原給linker register(r14)，並將program counter(r15)設定成linker register(r14)，即可結束name function，回到main。  

  
3.	Main function ：  
  ![image](https://user-images.githubusercontent.com/64779422/193545592-fdb87002-88c9-4ee7-a635-5578c9b01d05.png)
  ![image](https://user-images.githubusercontent.com/64779422/193545637-1072e2fa-73a7-4761-a796-5fb1890ebaa7.png)
  ![image](https://user-images.githubusercontent.com/64779422/193545647-0065f798-458c-46f5-bab4-71f024f5c1ce.png)
  ![image](https://user-images.githubusercontent.com/64779422/193545665-e895d11d-8ee3-48fc-ac97-b4700054a0d4.png)
  ![image](https://user-images.githubusercontent.com/64779422/193545675-ddcea37c-689c-40ab-9f04-254063e72fbf.png)
  
首先宣告4個char array，用來儲存組員名字與組別名稱，每個大小皆為12，依序為name1、name2、name3、teamname，並再宣告一個int array，為sid，大小為5，用來儲存所有的組員學號與總和。
接著執行Function1：name，呼叫name function，並將區域變數name1、name2、name3、teamname做為參數傳入name中(name(name1,name2,name3,teamname);)，執行name的任務。再執行Function2：id，並將區域變數sid陣列做為參數傳入id中(id(sid);)，執行id的任務。接著再依序使用兩個function所接到的參數進行印出Main Function的任務。
其餘皆與範例同。  

4.	drawJuliaSet：  
  ![image](https://user-images.githubusercontent.com/64779422/193545704-d29dc7bd-9a09-4386-8209-8a81b63b8eb0.png)
  ![image](https://user-images.githubusercontent.com/64779422/193545717-34267c09-cf66-41bd-ba99-9c8658f77466.png)
  ![image](https://user-images.githubusercontent.com/64779422/193545729-e9eb518d-25c4-4daf-9821-002126c59dd3.png)
  ![image](https://user-images.githubusercontent.com/64779422/193545744-18fbb750-0e30-4bdd-b1cf-df8524980764.png)
  ![image](https://user-images.githubusercontent.com/64779422/193545755-3f4cc8f5-33d0-43c5-b45b-76d2bc301e83.png)
  ![image](https://user-images.githubusercontent.com/64779422/193545765-68e46168-705e-4717-9d89-e3b184ed07d0.png)
  ![image](https://user-images.githubusercontent.com/64779422/193545783-bf19b448-005d-4a89-8824-3dad637fcb67.png)
  
首先先把從main傳進來的值存入4個宣告在drawJuliaSet.s檔案label中(cx,cy,width,height)，再將frame存入r10的暫存器。其餘皆與範例同。  
  
三、結果  
  ![image](https://user-images.githubusercontent.com/64779422/193545808-5397cb1b-dc05-4df4-a585-caa13159d55b.png)  
  ![image](https://user-images.githubusercontent.com/64779422/193545822-3332df24-4bea-47f9-b758-266acc96787d.png)  
  ![image](https://user-images.githubusercontent.com/64779422/193545840-7fd16732-7619-4829-94f7-5bc4e5cc2b22.png)  
  ![image](https://user-images.githubusercontent.com/64779422/193545845-4038eb4e-7092-49e3-8f19-c0a4c33b1f14.png)  
  ![image](https://user-images.githubusercontent.com/64779422/193545862-51f9b52a-7e0d-4ba7-9567-1c9203377a87.png)  
  

四、指定說明項目(memory dump)  
Name Function的起始位置：0x8c80  
Name Function的結束位置：0x8d04  

  ![image](https://user-images.githubusercontent.com/64779422/193545916-f07a787d-b5c6-4dcd-b45c-35a54847b342.png)
  ![image](https://user-images.githubusercontent.com/64779422/193545928-c4a5d4a2-944c-435d-baba-cfec5bec462b.png)


Id Function的起始位置：0x8860  
Id Function的結束位置：0x8994  

  ![image](https://user-images.githubusercontent.com/64779422/193545951-608aaa3e-cdfc-460a-a138-6e2c587aa511.png)
  ![image](https://user-images.githubusercontent.com/64779422/193545963-79d8ba3d-6235-4ab8-9bde-62c45e408db2.png)


drawJuliaSet Function的起始位置：0x8684  
drawJuliaSet Function的結束位置：0x8830  

  ![image](https://user-images.githubusercontent.com/64779422/193545977-1002a3f4-753d-437f-a5c6-1144af2d7ce4.png)
  ![image](https://user-images.githubusercontent.com/64779422/193545996-9bbb7502-e283-4c6f-a5d4-37cc731d38a2.png)


Frame 陣列的起始位置：0xbef69474
Frame陣列的終止位置：0xbefff474

  ![image](https://user-images.githubusercontent.com/64779422/193546021-02a9949b-9566-4f65-be25-5ce2fb4438f6.png)
  ![image](https://user-images.githubusercontent.com/64779422/193546037-d4c1c960-edef-429d-b081-c00487135fe2.png)


五、心得感想  
在此次的project中，利用實作來探索究竟我們所認識的一道道C程式語言的指令，要如何寫成組合語言程式。  
在寫drawJuliaSet最令人頭痛的就是迴圈太多，需要不斷的blanch，還有不知道要如何存取顏色到陣列。在存取顏色時，到底要用halfword 還是word ，經過多次的翻閱資料，發現顏色是以16位元表示所以需要用hword存取。還有在最後執行時，發現視窗是黑的還有幾條綠綠的線，剛開始都以為是存顏色的問題，最後才發現寫迴圈時y,忘記歸零了。  
在這次的project中，花了許多時間在debug，儘管在實作過程有許多挑戰，也花了非常多的精力去理解，但在實作後，不管是指令的操作、對暫存器的運作都有更進一步的了解。也發現到組合語言程式雖然指令不多，但是經過不管是條件執行還是不同的定址方式等的變換，一樣可以寫出好用的程式。   

