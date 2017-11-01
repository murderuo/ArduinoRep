aboneListesi=[
    [25,'ugur okur',96],
    [38,'feza coşkun',563],
    [89,'irem demir',123],
    [78,'boş kullanıcı',896],
    [41,'test user',36]
    ]
tabloVerisi=[]

while 1:
    aboneNoStr=input('abone numarasını giriniz: ')
    

    if aboneNoStr not in ['ç','Ç']:
        aboneNo=int(aboneNoStr)
        for aN in aboneListesi:
            if aboneNo==aN[0]:
                print ('abone ad soyad: ',aN[1])
                sEndeks=int(input('son endeksi giriniz: ') )
                tuketim=sEndeks-aN[2]
                odeme=float(tuketim*1.2)
                tabloVerisi.append([aN[0],aN[1],aN[2],sEndeks,tuketim,odeme])
                break
        else:
            print('abone yok')
            
    else:
        print ('çıkış yapıldı')
        print('Abone No\tAdı Soyadı\tİlk endeks\tSon Endeks\tTüketim\t\tÖdeme(TL)')
        for t in tabloVerisi:
            print(t[0],'\t\t',t[1],'\t',t[2],'\t\t',t[3],'\t\t',t[4],'\t\t',"%.2f"%t[5])
        
        break


        
