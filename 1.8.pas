PROGRAM BackPack;
CONST
  Max = 1000;
TYPE
  Arr = ARRAY[0 .. Max] OF RECORD
                             Price: INTEGER;
                             Weight: INTEGER
                           END;
  

VAR 
  Items, ResArr: Arr;
  MinPrice, MaxWeight, ResW, ICount, I: INTEGER;
  
PROCEDURE Package(ItemsArr: Arr; TotalW, TotalP, Ind: INTEGER);
VAR
  I, AddPrice, AddWeight: INTEGER;
BEGIN
  ItemsArr[Ind].Weight := 0;
  IF (TotalW <= MaxWeight) AND (TotalP >= MinPrice)
  THEN
    BEGIN
      ResW := TotalW;
      ResArr := ItemsArr;
    END
  ELSE
    IF ResW = 0
    THEN
      FOR I := 1 TO Max
      DO 
        IF (ItemsArr[I].Weight <> 0) AND (TotalW + ItemsArr[I].Weight < MaxWeight)
        THEN        
          Package(ItemsArr, TotalW + ItemsArr[I].Weight, TotalP + ItemsArr[I].Price, I)         
END;  
  
BEGIN
  READLN(ICount, MaxWeight, MinPrice);
  FOR I := 1 TO ICount
  DO
    READLN(Items[I].Weight, Items[I].Price);
  Package(Items, 0, 0, 0);
  WRITELN(ResW);
  IF ResW <> 0
  THEN
    FOR I := 1 TO ICount
    DO
      IF ResArr[I].Weight = 0
      THEN
        WRITE('1 ')
      ELSE
        WRITE('0 ')
END.