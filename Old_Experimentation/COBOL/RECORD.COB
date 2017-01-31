IDENTIFICATION DIVISION.
PROGRAM-ID. Acceptand.

DATA DIVISION.
WORKING-STORAGE SECTION.
01 StudentDetails.
    02   StudentId PIC 9(7).
    02   StudentName.
         03 Surname PIC X(8).
         03 Initials PIC XX.
    02   CourseCode PIC X(4).
    02   Gender PIC X.

PROCEDURE DIVISION.
Begin.
    DISPLAY "Enter the student details".
    ACCEPT  StudentDetails.
    DISPLAY "Name " StudentName SPACE Initials
    STOP RUN.

