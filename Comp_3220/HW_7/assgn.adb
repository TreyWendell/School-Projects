with Ada.Text_IO; use Ada.Text_IO;

package body Assgn is 

   --initialize first array (My_Array) with random binary values
   procedure Init_Array (Arr: in out BINARY_ARRAY) is
   begin
      Arr := (others => BINARY_NUMBER(0));
      Arr(16) := BINARY_NUMBER(1);
   end Init_Array;

   procedure Reverse_Bin_Arr (Arr : in out BINARY_ARRAY) is
      NewArr : BINARY_ARRAY;
   begin
      NewArr := (others => BINARY_NUMBER(0));
   
      for I in Arr'Range loop
         NewArr(I) := Arr(Arr'Last + 1 - I);
      end loop;
   
      Arr := NewArr;
   end Reverse_Bin_Arr;
   
   procedure Print_Bin_Arr (Arr : in BINARY_ARRAY) is
   begin
      for I in Arr'Range loop
         Put(BINARY_NUMBER'Image (Arr(I)));
      end loop;
      New_Line;
   end Print_Bin_Arr;

   --Convert Integer to Binary Array
   function Int_To_Bin(Num : in INTEGER) return BINARY_ARRAY is
      Arr : BINARY_ARRAY := (others => 0);
      int : INTEGER := Num;
   begin
      for I in reverse Arr'Range loop
         Arr(I) := int mod 2;
         int := int / 2;
      end loop;
      return Arr;
   end Int_To_Bin;

   --convert binary number to integer
   function Bin_To_Int (Arr : in BINARY_ARRAY) return INTEGER is
      int    : INTEGER;
      revArr : BINARY_ARRAY := Arr;
      retval : INTEGER := 0;
   begin
      Reverse_Bin_Arr(revArr);        
   
      for I in revArr'Range loop
         int := 2**(I-1) * revArr(I);
         retval := retval + int;
      end loop;
   
      return retval;
   end Bin_To_Int;

   --overloaded + operator to add two BINARY_ARRAY types together
   function "+" (Left, Right : in BINARY_ARRAY) return BINARY_ARRAY is
      sum    : INTEGER;
      carry  : INTEGER := 0;
      retval : BINARY_ARRAY := (others => 0);
   begin
      for I in reverse Left'Range loop
         sum := Left(I) + Right(I) + carry;
         retval(I) := sum mod 2;
         carry := sum / 2;
      end loop;
      return retval;
   end "+";

   --overloaded + operator to add an INTEGER type and a BINARY_ARRAY type together
   function "+" (Left : in INTEGER; Right : in BINARY_ARRAY) return BINARY_ARRAY is
      LeftArr : BINARY_ARRAY := Int_To_Bin(Left);
   begin
      return LeftArr + Right;
   end "+";
   --overloaded - operator to subtract one BINARY_ARRAY type from another			 
   function "-" (Left, Right : in BINARY_ARRAY) return BINARY_ARRAY is
      RightComplement : BINARY_ARRAY := (others => 0);
      retval : BINARY_ARRAY := (others => 0);
   begin
    -- Flip binary number and add one.
      for I in Right'Range loop
         RightComplement(I) := (Right(I) + 1) mod 2;
      end loop;
      RightComplement := INTEGER(1) + RightComplement;
   
    -- Add binary numbers.
      retval := RightComplement + Left;
   
      return retval;
   end "-";

   --overloaded - operator to subtract a BINARY_ARRAY type from an INTEGER type
   function "-" (Left : in Integer; Right : in BINARY_ARRAY) return BINARY_ARRAY is
      LeftArr : BINARY_ARRAY := Int_To_Bin(Left);
   begin
      return LeftArr - Right;
   end "-";

end Assgn;