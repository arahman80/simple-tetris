program Tetris;

uses
  SysUtils, Crt;

procedure CursorOff;
begin
  Write(#27'[?25l');
end;

type
  TPieceMap = array[0..3, 0..1] of Byte;
  TBoard = array[0..20] of LongWord;
  TBag = array[0..6] of Byte;
  
  TKick = record
    X, Y: ShortInt;
  end;
  
  TKickTable = array[0..3, 0..3, 0..4] of TKick;
  
  TTetrisPiece = record
    X: ShortInt;
    Y: ShortInt;
    PieceType: String;
    SelectedRotation: Byte;
    PieceMap: ^TPieceMap;
  end;
  
  TTetrisBag = record
    Bag: TBag;
    Index: Byte;
    RngState: Byte;
  end;

const
  OPiece: TPieceMap = (($66, $00), ($66, $00), ($66, $00), ($66, $00));
  IPiece: TPieceMap = (($0F, $00), ($22, $22), ($00, $F0), ($44, $44));
  TPiece: TPieceMap = (($4E, $00), ($46, $40), ($0E, $40), ($4C, $40));
  SPiece: TPieceMap = (($6C, $00), ($46, $20), ($6C, $00), ($8C, $40));
  ZPiece: TPieceMap = (($C6, $00), ($26, $40), ($C6, $00), ($4C, $80));
  LPiece: TPieceMap = (($8E, $00), ($64, $40), ($E2, $00), ($44, $C0));
  JPiece: TPieceMap = (($2E, $00), ($44, $60), ($E8, $00), ($C4, $40));

  SRSNorm: TKickTable = (
    // From rotation 0
    (((X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0)),      // 0->0 (unused)
     ((X:0; Y:0), (X:-1; Y:0), (X:-1; Y:1), (X:0; Y:-2), (X:-1; Y:-2)), // 0->1
     ((X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0)),      // 0->2 (unused)
     ((X:0; Y:0), (X:1; Y:0), (X:1; Y:1), (X:0; Y:-2), (X:1; Y:-2))),   // 0->3
    
    // From rotation 1
    (((X:0; Y:0), (X:1; Y:0), (X:1; Y:-1), (X:0; Y:2), (X:1; Y:2)),      // 1->0
     ((X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0)),       // 1->1 (unused)
     ((X:0; Y:0), (X:1; Y:0), (X:1; Y:-1), (X:0; Y:2), (X:1; Y:2)),      // 1->2
     ((X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0))),      // 1->3 (unused)
    
    // From rotation 2
    (((X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0)),       // 2->0 (unused)
     ((X:0; Y:0), (X:-1; Y:0), (X:-1; Y:1), (X:0; Y:-2), (X:-1; Y:-2)),  // 2->1
     ((X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0)),       // 2->2 (unused)
     ((X:0; Y:0), (X:1; Y:0), (X:1; Y:1), (X:0; Y:-2), (X:1; Y:-2))),    // 2->3
    
    // From rotation 3
    (((X:0; Y:0), (X:-1; Y:0), (X:-1; Y:-1), (X:0; Y:2), (X:-1; Y:2)),   // 3->0
     ((X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0)),       // 3->1 (unused)
     ((X:0; Y:0), (X:-1; Y:0), (X:-1; Y:-1), (X:0; Y:2), (X:-1; Y:2)),   // 3->2
     ((X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0)))       // 3->3 (unused)
  );

  SRSIPiece: TKickTable = (
    // From rotation 0
    (((X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0)),       // 0->0 (unused)
     ((X:0; Y:0), (X:-2; Y:0), (X:1; Y:0), (X:-2; Y:-1), (X:1; Y:2)),    // 0->1
     ((X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0)),       // 0->2 (unused)
     ((X:0; Y:0), (X:-1; Y:0), (X:2; Y:0), (X:-1; Y:2), (X:2; Y:-1))),   // 0->3
    
    // From rotation 1
    (((X:0; Y:0), (X:2; Y:0), (X:-1; Y:0), (X:2; Y:1), (X:-1; Y:-2)),    // 1->0
     ((X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0)),       // 1->1 (unused)
     ((X:0; Y:0), (X:-1; Y:0), (X:2; Y:0), (X:-1; Y:2), (X:2; Y:-1)),    // 1->2
     ((X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0))),      // 1->3 (unused)
    
    // From rotation 2
    (((X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0)),       // 2->0 (unused)
     ((X:0; Y:0), (X:1; Y:0), (X:-2; Y:0), (X:1; Y:-2), (X:-2; Y:1)),    // 2->1
     ((X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0)),       // 2->2 (unused)
     ((X:0; Y:0), (X:2; Y:0), (X:-1; Y:0), (X:2; Y:1), (X:-1; Y:-2))),   // 2->3
    
    // From rotation 3
    (((X:0; Y:0), (X:1; Y:0), (X:-2; Y:0), (X:1; Y:-2), (X:-2; Y:1)),    // 3->0
     ((X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0)),       // 3->1 (unused)
     ((X:0; Y:0), (X:-2; Y:0), (X:1; Y:0), (X:-2; Y:-1), (X:1; Y:2)),    // 3->2
     ((X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0), (X:0; Y:0)))       // 3->3 (unused)
  );

var
  Board: TBoard;
  Bag: TTetrisBag;
  Piece: TTetrisPiece;
  C: Char;
  LastFallTime: Int64;
  FallDelay: Int64;

procedure InitBoard(var Board: TBoard);
var
  I: ShortInt;
begin
  for I := 0 to 19 do
    Board[I] := $2004; // 0b0010000000000100
  Board[20] := $FFFF; // 0b1111111111111111
end;

function IsValid(var Piece: TTetrisPiece; var Board: TBoard; 
                 XShift, YShift: ShortInt; Rotate: ShortInt; Clockwise: ShortInt): Boolean;
var
  Rot: Byte;
  UpSeg, LowSeg: Byte;
  Seg1, Seg2, Seg3, Seg4: Byte;
  Seg1Shifted, Seg2Shifted, Seg3Shifted, Seg4Shifted: LongWord;
begin
  Rot := Piece.SelectedRotation;
  if Rotate <> 0 then
  begin
    if Clockwise <> 0 then
      Rot := (Rot + 1) mod 4
    else
      Rot := (Rot + 3) mod 4;
  end;

  UpSeg := Piece.PieceMap^[Rot, 0];
  LowSeg := Piece.PieceMap^[Rot, 1];

  Seg1 := (UpSeg and $F0) shr 4;
  Seg2 := UpSeg and $0F;
  Seg3 := (LowSeg and $F0) shr 4;
  Seg4 := LowSeg and $0F;

  Seg1Shifted := LongWord(Seg1) shl (10 - 4 - (Piece.X + XShift));
  Seg2Shifted := LongWord(Seg2) shl (10 - 4 - (Piece.X + XShift));
  Seg3Shifted := LongWord(Seg3) shl (10 - 4 - (Piece.X + XShift));
  Seg4Shifted := LongWord(Seg4) shl (10 - 4 - (Piece.X + XShift));

  IsValid := True;
  if (Board[Piece.Y + 0 + YShift] and Seg1Shifted) <> 0 then IsValid := False;
  if (Board[Piece.Y + 1 + YShift] and Seg2Shifted) <> 0 then IsValid := False;
  if (Board[Piece.Y + 2 + YShift] and Seg3Shifted) <> 0 then IsValid := False;
  if (Board[Piece.Y + 3 + YShift] and Seg4Shifted) <> 0 then IsValid := False;
end;

procedure GroundPiece(var Piece: TTetrisPiece; var Board: TBoard);
var
  Rot: Byte;
  UpSeg, LowSeg: Byte;
  Seg1, Seg2, Seg3, Seg4: Byte;
  Seg1Shifted, Seg2Shifted, Seg3Shifted, Seg4Shifted: LongWord;
begin
  Rot := Piece.SelectedRotation;
  UpSeg := Piece.PieceMap^[Rot, 0];
  LowSeg := Piece.PieceMap^[Rot, 1];

  Seg1 := (UpSeg and $F0) shr 4;
  Seg2 := UpSeg and $0F;
  Seg3 := (LowSeg and $F0) shr 4;
  Seg4 := LowSeg and $0F;

  Seg1Shifted := LongWord(Seg1) shl (10 - 4 - Piece.X);
  Seg2Shifted := LongWord(Seg2) shl (10 - 4 - Piece.X);
  Seg3Shifted := LongWord(Seg3) shl (10 - 4 - Piece.X);
  Seg4Shifted := LongWord(Seg4) shl (10 - 4 - Piece.X);

  Board[Piece.Y + 0] := Board[Piece.Y + 0] or Seg1Shifted;
  Board[Piece.Y + 1] := Board[Piece.Y + 1] or Seg2Shifted;
  Board[Piece.Y + 2] := Board[Piece.Y + 2] or Seg3Shifted;
  Board[Piece.Y + 3] := Board[Piece.Y + 3] or Seg4Shifted;
end;

procedure ClearRows(var Board: TBoard);
var
  Dst, Src: ShortInt;
begin
  Dst := 19;
  for Src := 19 downto 0 do
  begin
    if (Board[Src] and $1FFC) <> $1FFC then
    begin
      Board[Dst] := Board[Src];
      Dec(Dst);
    end;
  end;

  while Dst >= 0 do
  begin
    Board[Dst] := $2004;
    Dec(Dst);
  end;
end;

function XorShift8(var State: Byte): Byte;
var
  X: Byte;
begin
  X := State;
  X := X xor (X shl 3);
  X := X xor (X shr 5);
  X := X xor (X shl 2);
  State := X;
  XorShift8 := X;
end;

procedure ShuffleBag(var Bag: TBag; var RandomState: Byte);
var
  I: ShortInt;
  J: Byte;
  Temp: Byte;
begin
  for I := 0 to 6 do
    Bag[I] := I;

  for I := 0 to 6 do
  begin
    J := XorShift8(RandomState) mod 7;
    Temp := Bag[I];
    Bag[I] := Bag[J];
    Bag[J] := Temp;
  end;
end;

procedure InitBag(var Bag: TTetrisBag; Seed: Byte);
begin
  Bag.RngState := Seed;
  Bag.Index := 7;
end;

function NextPiece(var Bag: TTetrisBag): Byte;
begin
  if Bag.Index >= 7 then
  begin
    ShuffleBag(Bag.Bag, Bag.RngState);
    Bag.Index := 0;
  end;

  NextPiece := Bag.Bag[Bag.Index];
  Inc(Bag.Index);
end;

procedure SelectPiece(selector: Byte; var Piece: TTetrisPiece);
begin
  Piece.X := 0;
  Piece.Y := 0;
  Piece.SelectedRotation := 0;

  case selector of
    0: begin
         Piece.PieceMap := @OPiece;
         Piece.PieceType := 'OPiece';
       end;
    1: begin
         Piece.PieceMap := @IPiece;
         Piece.PieceType := 'I';
       end;
    2: begin
         Piece.PieceMap := @TPiece;
         Piece.PieceType := 'TPiece';
       end;
    3: begin
         Piece.PieceMap := @SPiece;
         Piece.PieceType := 'SPiece';
       end;
    4: begin
         Piece.PieceMap := @ZPiece;
         Piece.PieceType := 'ZPiece';
       end;
    5: begin
         Piece.PieceMap := @LPiece;
         Piece.PieceType := 'LPiece';
       end;
    6: begin
         Piece.PieceMap := @JPiece;
         Piece.PieceType := 'JPiece';
       end;
  end;
end;

procedure PrintGame(var Board: TBoard; var Piece: TTetrisPiece);
var
  Temp: TBoard;
  I, Y, X: ShortInt;
  Rot: Byte;
  UpSeg, LowSeg: Byte;
  Seg1, Seg2, Seg3, Seg4: Byte;
begin
  GoToXY(1, 1);
  for I := 0 to 20 do
    Temp[I] := Board[I];

  Rot := Piece.SelectedRotation;
  UpSeg := Piece.PieceMap^[Rot, 0];
  LowSeg := Piece.PieceMap^[Rot, 1];

  Seg1 := (UpSeg and $F0) shr 4;
  Seg2 := UpSeg and $0F;
  Seg3 := (LowSeg and $F0) shr 4;
  Seg4 := LowSeg and $0F;

  Temp[Piece.Y + 0] := Temp[Piece.Y + 0] or (LongWord(Seg1) shl (10 - 4 - Piece.X));
  Temp[Piece.Y + 1] := Temp[Piece.Y + 1] or (LongWord(Seg2) shl (10 - 4 - Piece.X));
  Temp[Piece.Y + 2] := Temp[Piece.Y + 2] or (LongWord(Seg3) shl (10 - 4 - Piece.X));
  Temp[Piece.Y + 3] := Temp[Piece.Y + 3] or (LongWord(Seg4) shl (10 - 4 - Piece.X));

  WriteLn;
  for Y := 0 to 19 do
  begin
    Write('<!');
    for X := 12 downto 3 do
    begin
      if (Temp[Y] and (1 shl X)) <> 0 then
        Write('[ ]')
      else
        Write(' . ');
    end;
    Write('!>');
    WriteLn;
  end;
  Write('<!==============================!>');
  Writeln;
end;

procedure RotateSRS(var Piece: TTetrisPiece; var Board: TBoard; Clockwise: ShortInt);
var
  FromRot, ToRot: ShortInt;
  I: Integer;
begin
  FromRot := Piece.SelectedRotation;
  if Clockwise <> 0 then
    ToRot := (FromRot + 1) mod 4
  else
    ToRot := (FromRot + 3) mod 4;

  if Piece.PieceType = 'I' then
  begin
    for I := 0 to 4 do
    begin
      if IsValid(Piece, Board, SRSIPiece[FromRot, ToRot, I].X, SRSIPiece[FromRot, ToRot, I].Y, 1, Clockwise) then
      begin
        Piece.X := Piece.X + SRSIPiece[FromRot, ToRot, I].X;
        Piece.Y := Piece.Y + SRSIPiece[FromRot, ToRot, I].Y;
        Piece.SelectedRotation := ToRot;
        Break;
      end;
    end;
  end
  else
  begin
    for I := 0 to 4 do
    begin
      if IsValid(Piece, Board, SRSNorm[FromRot, ToRot, I].X, SRSNorm[FromRot, ToRot, I].Y, 1, Clockwise) then
      begin
        Piece.X := Piece.X + SRSNorm[FromRot, ToRot, I].X;
        Piece.Y := Piece.Y + SRSNorm[FromRot, ToRot, I].Y;
        Piece.SelectedRotation := ToRot;
        Break;
      end;
    end;
  end;
end;

begin
  ClrScr;
  CursorOff;
  InitBoard(Board);
  InitBag(Bag, 123);
  SelectPiece(NextPiece(Bag), Piece);
  
  FallDelay := 500;
  LastFallTime := GetTickCount64;
  
  PrintGame(Board, Piece);

  repeat
    if Crt.KeyPressed then
    begin
      C := Crt.ReadKey;
      case C of
        'w', 'W': RotateSRS(Piece, Board, 1);
        's', 'S': RotateSRS(Piece, Board, 0);
        'a', 'A': if IsValid(Piece, Board, -1, 0, 0, 0) then
                    Piece.X := Piece.X - 1;
        'd', 'D': if IsValid(Piece, Board, 1, 0, 0, 0) then
                    Piece.X := Piece.X + 1;
        'f', 'F': LastFallTime := GetTickCount64 - FallDelay;
        ' ': begin
               while IsValid(Piece, Board, 0, 1, 0, 0) do
                 Piece.Y := Piece.Y + 1;
               LastFallTime := GetTickCount64 - FallDelay;
             end;
        'q', 'Q', #27: Halt(0);
      end;
      PrintGame(Board, Piece);
    end;

    if GetTickCount64 - LastFallTime >= FallDelay then
    begin
      if IsValid(Piece, Board, 0, 1, 0, 0) then
      begin
        Piece.Y := Piece.Y + 1;
        PrintGame(Board, Piece);
      end
      else
      begin
        GroundPiece(Piece, Board);
        ClearRows(Board);
        SelectPiece(NextPiece(Bag), Piece);
        if not IsValid(Piece, Board, 0, 0, 0, 0) then
        begin
          WriteLn('You Lost!');
          WriteLn('Press any key to exit...');
          Crt.ReadKey;
          Halt(0);
        end;
        PrintGame(Board, Piece);
      end;
      LastFallTime := GetTickCount64;
    end;

    Sleep(50);
  until False;
end.