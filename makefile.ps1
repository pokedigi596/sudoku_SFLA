if ($args[0] -eq "logic") {
	rm logic_result\*
	for ($i = 0; $i -le 99; $i = $i + 1)
	{
		.\sudoku_main.exe instances\logic-solvable\aiescargot.txt 3 5 logic_result\aiescargot-test.txt
		.\sudoku_main.exe instances\logic-solvable\coly013.txt 3 5 logic_result\coly013-test.txt
		.\sudoku_main.exe instances\logic-solvable\goldennugget.txt 3 5 logic_result\goldennugget-test.txt
		.\sudoku_main.exe instances\logic-solvable\platinumblond.txt 3 5 logic_result\platinumblond-test.txt
		.\sudoku_main.exe instances\logic-solvable\reddwarf.txt 3 5 logic_result\reddwarf-test.txt
		.\sudoku_main.exe instances\logic-solvable\sabuncu1.txt 3 5 logic_result\sabuncu1-test.txt
		.\sudoku_main.exe instances\logic-solvable\sabuncu2.txt 3 5 logic_result\sabuncu2-test.txt
		.\sudoku_main.exe instances\logic-solvable\sabuncu3.txt 3 5 logic_result\sabuncu3-test.txt
		.\sudoku_main.exe instances\logic-solvable\sabuncu4.txt 3 5 logic_result\sabuncu4-test.txt
		.\sudoku_main.exe instances\logic-solvable\sabuncu5.txt 3 5 logic_result\sabuncu5-test.txt
		.\sudoku_main.exe instances\logic-solvable\sabuncu6.txt 3 5 logic_result\sabuncu6-test.txt
		.\sudoku_main.exe instances\logic-solvable\sabuncu7.txt 3 5 logic_result\sabuncu7-test.txt
		.\sudoku_main.exe instances\logic-solvable\sabuncu8.txt 3 5 logic_result\sabuncu8-test.txt
		.\sudoku_main.exe instances\logic-solvable\sabuncu9.txt 3 5 logic_result\sabuncu9-test.txt
		.\sudoku_main.exe instances\logic-solvable\sabuncu10.txt 3 5 logic_result\sabuncu10-test.txt
		.\sudoku_main.exe instances\logic-solvable\tarx0134.txt 3 5 logic_result\tarx0134-test.txt
	}
}
elseif ($args[0] -eq "autotest") {
	if ($args[1] -eq "3") {
		rm 9x9_result\*
		for ($i = 0; $i -le 100; $i = $i + 5) {
			echo "$i% fixed"
			for ($j = 0; $j -le 99; $j++) {
				$line = '_'
				$file = "instances\general\inst9x9_$i$line$j.txt"
				.\sudoku_main.exe $file 3 5 9x9_result\9$line$i-test.txt
			}
		}
	}
	elseif ($args[1] -eq "4") {
		rm 16x16_result\*
		for ($i = 0; $i -le 100; $i = $i + 5) {
			echo "$i% fixed"
			for ($j = 0; $j -le 99; $j++) {
				$line = '_'
				$file = "instances\general\inst16x16_$i$line$j.txt"
				.\sudoku_main.exe $file 3 5 16x16_result\16$line$i-test.txt
			}
		}
	}
	elseif ($args[1] -eq "5") {
		rm 25x25_result\*
		for ($i = 40; $i -le 40; $i = $i + 5) {
			echo "$i% fixed"
			for ($j = 0; $j -le 99; $j++) {
				$line = '_'
				$file = "instances\general\inst25x25_$i$line$j.txt"
				if ($i -eq 35) {
					.\sudoku_main.exe $file 5 60 25x25_result\25$line$i-test.txt
				}
				elseif ($i -eq 40) {
					.\sudoku_main.exe $file 5 60 25x25_result\25$line$i-test.txt
				}
				elseif ($i -eq 45) {
					.\sudoku_main.exe $file 10 40 25x25_result\25$line$i-test.txt
				}
				elseif ($i -eq 50) {
					.\sudoku_main.exe $file 5 80 25x25_result\25$line$i-test.txt
				}
				else {
					.\sudoku_main.exe $file 3 5 25x25_result\25$line$i-test.txt
				}
			}
		}
	}
	else {
		echo "Please Enter Puzzle Size!"
	}
}
elseif ($args[0] -eq "data") {
	echo "logic"
		.\calculate_data.exe logic_result\aiescargot-test.txt
		.\calculate_data.exe logic_result\coly013-test.txt
		.\calculate_data.exe logic_result\goldennugget-test.txt
		.\calculate_data.exe logic_result\platinumblond-test.txt
		.\calculate_data.exe logic_result\reddwarf-test.txt
		.\calculate_data.exe logic_result\sabuncu1-test.txt
		.\calculate_data.exe logic_result\sabuncu2-test.txt
		.\calculate_data.exe logic_result\sabuncu3-test.txt
		.\calculate_data.exe logic_result\sabuncu4-test.txt
		.\calculate_data.exe logic_result\sabuncu5-test.txt
		.\calculate_data.exe logic_result\sabuncu6-test.txt
		.\calculate_data.exe logic_result\sabuncu7-test.txt
		.\calculate_data.exe logic_result\sabuncu8-test.txt
		.\calculate_data.exe logic_result\sabuncu9-test.txt
		.\calculate_data.exe logic_result\sabuncu10-test.txt
		.\calculate_data.exe logic_result\tarx0134-test.txt
	echo "9x9"
	for ($i = 0; $i -le 100; $i = $i + 5) {
		$line = '_'
		$file = "9x9_result\9$line$i-test.txt"
		.\calculate_data.exe $file
	}
	echo "16x16"
	for ($i = 0; $i -le 100; $i = $i + 5) {
		$line = '_'
		$file = "16x16_result\16$line$i-test.txt"
		.\calculate_data.exe $file
	}
	echo "25x25"
	for ($i = 0; $i -le 100; $i = $i + 5) {
		$line = '_'
		$file = "25x25_result\25$line$i-test.txt"
		.\calculate_data.exe $file
	}
}
else {
	g++ -c -O3 -std=c++0x src\num_set.cpp -o obj\num_set.o
	g++ -c -O3 -std=c++0x src\sudoku_board.cpp -o obj\sudoku_board.o
	g++ -c -O3 -std=c++0x src\sudoku_main.cpp -o obj\sudoku_main.o
	g++ -c -O3 -std=c++0x src\sudoku_solver.cpp -o obj\sudoku_solver.o
	g++ -o sudoku_main.exe obj\num_set.o obj\sudoku_board.o obj\sudoku_main.o obj\sudoku_solver.o

	#g++ src\num_set.cpp src\sudoku_board.cpp src\sudoku_main.cpp src\sudoku_solver.cpp -o sudoku_main.exe
	g++ src\calculate_data.cpp -o calculate_data.exe
}