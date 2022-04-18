//makerec.cc
#include "buffile.h"
#include "recordng.h"
#include "delim.h"
#include <iostream>
#include "recfile.h"
#include <fstream>
#include <iomanip>
#include "iobuffer.h"
#include "student.h"
#include <string>

//file에 write 한 후에 read하여 출력하는 프로그램 작성 실습 
// create two files with the recordings of Figure 7.2
//    the file "record.dat" is created using class BufferFile
//    the file "record2.dat" is created using class RecordFile<Recording>
using namespace std;

istream& operator >> (istream& stream, Student& s)
{ // read fields from file
	char delim;
	stream.getline(s.Id, 30, '|');
	if (strlen(s.Id) == 0) return stream;
	stream.getline(s.Name, 30, '|');
	stream.getline(s.Address, 30, '|');
	stream.getline(s.DateEnroll, 30, '|');
	stream.getline(s.temp, 15, '|');
	s.NumberCredit = stoi(s.temp);
	cout << endl << "istream.getline(object, size, '|') 실행됨" << endl;
	return stream;
}
ostream& operator << (ostream& stream, Student& s)
{ // insert fields into file
	cout << "Person 객체를 출력한다" << endl;
	stream << s.Id << '|' << s.Name << '|'
		<< s.Address << '|' << s.DateEnroll << '|'
		<< s.NumberCredit << '|';
	cout << endl;
	return stream;
}



int main(void)
{
	int recaddr;
	int result;
	DelimFieldBuffer::SetDefaultDelim('|');
	DelimFieldBuffer Buffer;
	Recording::InitBuffer(Buffer);
	BufferFile IndexedFile(Buffer);

	char* myfile = "record.ind";
	result = IndexedFile.Create(myfile, ios::out);
	cout << "main()::create file " << result << endl;
	if (!result)
	{
		cout << "main()::Unable to create file " << myfile << endl;
		result = IndexedFile.Open(myfile, ios::out);
		cout << "main()::open file " << result << endl;
		if (!result)
		{
			cout << "main()::Unable to open file " << myfile << endl;
			system("pause");

			return 0;
		}
	}
	
	
	//RecordFile<Recording> RecordedFile(Buffer);
	//RecordedFile.Create("recording.dat", ios::out);
	/*
	Recording* R[10]; //=> 1장에서 만든 Student record로 변경한다.
	R[0] = new Recording("LON", "2312", "Romeo and Juliet", "Prokofiev", "Maazel");
	R[1] = new Recording("RCA", "2626", "Quartet in C Sharp Minor", "Beethoven", "Julliard");
	R[2] = new Recording("WAR", "23699", "Touchstone", "Corea", "Corea");
	R[3] = new Recording("ANG", "3795", "Symphony No. 9", "Beethoven", "Giulini");
	R[4] = new Recording("COL", "38358", "Nebraska", "Springsteen", "Springsteen");
	R[5] = new Recording("DG", "18807", "Symphony No. 9", "Beethoven", "Karajan");
	R[6] = new Recording("MER", "75016", "Coq d'or Suite", "Rimsky-Korsakov", "Leinsdorf");
	R[7] = new Recording("COL", "31809", "Symphony No. 9", "Dvorak", "Bernstein");
	R[8] = new Recording("DG", "139201", "Violin Concerto", "Beethoven", "Ferras");
	R[9] = new Recording("FF", "245", "Good News", "Sweet Honey in the Rock", "Sweet Honey in the Rock");
	for (int i = 0; i < 10; i++)
	{
		//TextIndex에 없으면 index.Insert()
		recaddr = RecordedFile.Write(*R[i]);
		cout << "Recordin2 R[" << i << "] at recaddr " << recaddr << endl;
		delete R[i];
	}
	//IndexedFile, RecordFile에 write한 레코드를 읽는 코드를 추가한다
	//IndexedFile에 생성된 index를 저장
	*/
	
	//IndexedFile.Close();
	//RecordedFile.Close();

	
	//char *keyname = "DG18807"; 화면에서 입력받아서 반복 실행하게 처리
	//입력된 key에 대한 index를 search한 후에 해당 레코드를 출력하는 프로그램 - makeind-2.cpp를 참조하여
	// 본 프로그램을 수정하여 완성

	RecordFile<Student> RecordedFile(Buffer);
	RecordedFile.Create("recording.dat", ios::out);

	IndexedFile.Open("record.ind", ios::out); //다시 open
	RecordedFile.Open("recording.dat", ios::out);//다시 open

	Student* R[3]; //=> 1장에서 만든 Student record로 변경한다.
	for (int i = 0; i < 10; i++) {
		R[i] = new Student();
		cin >> *R[i];
	}
	for (int i = 0; i < 10; i++)
	{
		//TextIndex에 없으면 index.Insert()
		recaddr = RecordedFile.Write(*R[i]);
		cout << "Recordin2 R[" << i << "] at recaddr " << recaddr << endl;
		delete R[i];
	}

	IndexedFile.Close();
	RecordedFile.Close();

	system("pause");
	return 1;
}


