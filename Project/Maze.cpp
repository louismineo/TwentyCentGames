#include "pch.hpp"

AEGfxVertexList* pMeshCellOutline = 0;
AEGfxVertexList* pMeshMazeWindow = 0;
AEGfxVertexList* pMeshSolidSquare_PATH = 0;
AEGfxVertexList* pMeshSolidSquare_WALL = 0;

float MC_positionX;
float MC_positionY;
AEGfxVertexList* pMesh_MainCharacter = 0;
int starting_Xposition = 7;
int starting_Yposition = 0;

Maze_Struct* Maze;


int maze_iswall_isnotwall[noOfRows][noOfCols] =
{
	/*
	1,1,1,1,1, 1,1,0,1,1, 1,1,1,1,1,
	1,0,0,0,1, 0,0,0,0,0, 0,0,0,0,1,
	1,0,1,0,1, 0,1,1,1,1, 1,0,1,1,1,
	1,0,1,0,1, 0,0,0,1,0, 1,0,0,0,1,
	1,0,1,1,1, 1,1,0,1,0, 1,1,1,0,1,
	1,0,1,0,0, 0,0,0,1,0, 0,0,1,0,1,
	1,0,1,0,1, 1,1,1,1,1, 1,0,1,1,1,
	1,0,0,0,1, 0,0,0,0,0, 1,0,0,0,1,
	1,0,1,1,1, 0,1,1,1,0, 1,0,1,0,1,
	1,0,1,0,0, 0,1,0,1,0, 0,0,1,0,1,
	1,0,1,0,1, 1,1,0,1,1, 1,1,1,0,1,
	1,0,0,0,1, 0,0,0,1,0, 0,0,1,0,1,
	1,1,1,1,1, 0,1,0,1,0, 1,0,1,0,1,
	1,0,0,0,0, 0,1,0,0,0, 1,0,0,0,1,
	1,1,1,1,1, 1,1,0,1,1, 1,1,1,1,1
	*/

	1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,1,0,1,
	1,0,1,1,1, 1,1,0,1,1, 1,0,1,0,1,
	1,0,0,0,1, 0,0,0,1,0, 0,0,1,0,1,
	1,1,1,1,1, 0,1,1,1,0, 1,1,1,0,1,
	1,0,0,0,1, 0,1,0,0,0, 1,0,0,0,1,
	1,0,1,0,1, 0,1,0,1,1, 1,0,1,1,1,
	0,0,1,0,0, 0,1,0,1,0, 0,0,0,0,0,
	1,0,1,1,1, 1,1,0,1,1, 1,1,1,0,1,
	1,0,1,0,0, 0,1,0,0,0, 1,0,0,0,1,
	1,0,1,1,1, 0,1,1,1,0, 1,0,1,1,1,
	1,0,0,0,1, 0,0,0,0,0, 1,0,0,0,1,
	1,0,1,0,1, 1,1,0,1,1, 1,1,1,0,1,
	1,0,1,0,0, 0,1,0,0,0, 0,0,0,0,1,
	1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1

};


Maze_Struct* CreateMaze(int Exe_WindowHeight, int Exe_WindowWidth, int noOfRows, int noOfCols)
{
	Maze_Struct* Maze = new Maze_Struct;


	//INITIALIZING THE DIMENSIONS STRUCT
	Maze->specifications.noOfRows = noOfRows;
	Maze->specifications.noOfCols = noOfCols;
	Maze->specifications.mazeWindowHeight = ((float)Exe_WindowHeight / 6.0f) * 5;
	Maze->specifications.mazeWindowWidth = (float)Exe_WindowWidth / 2.0f;
	Maze->specifications.cellHeight = Maze->specifications.mazeWindowHeight / noOfRows;
	Maze->specifications.cellWidth = Maze->specifications.mazeWindowWidth / noOfCols;
	Maze->specifications.MazeWindowStart_X = Exe_WindowWidth / 2.0f / -2;
	Maze->specifications.MazeWindowStart_Y = (Exe_WindowHeight / 6.0f * 5 / -2);

	// Init the grid cells
	for (int r = 0; r < Maze->specifications.noOfRows; r++)
	{
		for (int c = 0; c < Maze->specifications.noOfCols; c++)
		{

			Maze->grid[r][c].is_wall = maze_iswall_isnotwall[r][c];
			//Maze->grid[r][c].is_PlayerPos = 0;

		}
	}

	//Maze->grid[0][7].is_PlayerPos = 1;


	return Maze;
}

void MAZE_CreateMESH_MazeWindow2(AEGfxVertexList*& MazeWindow_Var, Maze_Struct* Maze, int colour_HEXA)
{
	AEGfxMeshStart();
	// This shape has 5 vertices
	AEGfxVertexAdd(0.0f, 0.0f, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(Maze->specifications.mazeWindowWidth, 0.0f, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(Maze->specifications.mazeWindowWidth, Maze->specifications.mazeWindowHeight, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(0.0f, Maze->specifications.mazeWindowHeight, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(0.0f, 0.0f, colour_HEXA, 0.0f, 0.0f);
	MazeWindow_Var = AEGfxMeshEnd();
}

void MAZE_CreateMESH_CellOutline2(AEGfxVertexList*& CellOutlineMesh_Var, Maze_Struct* Maze, int colour_HEXA)
{
	AEGfxMeshStart();
	AEGfxVertexAdd(0.0f, 0.0f, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(Maze->specifications.cellWidth, 0.0f, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(Maze->specifications.cellWidth, Maze->specifications.cellHeight, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(0.0f, Maze->specifications.cellHeight, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(0.0f, 0.0f, colour_HEXA, 0.0f, 0.0f);
	CellOutlineMesh_Var = AEGfxMeshEnd();
}

void MAZE_CreateSolidCell2(AEGfxVertexList*& SolidCellMesh_Var, Maze_Struct* Maze, int colour_HEXA)
{
	AEGfxMeshStart();
	AEGfxTriAdd(
		0, 0, colour_HEXA, 0.0f, 1.0f,
		0, Maze->specifications.cellHeight, colour_HEXA, 1.0f, 1.0f,
		Maze->specifications.cellWidth, 0, colour_HEXA, 0.0f, 0.0f);
	AEGfxTriAdd(
		0, Maze->specifications.cellHeight, colour_HEXA, 1.0f, 1.0f,
		Maze->specifications.cellWidth, Maze->specifications.cellHeight, colour_HEXA, 1.0f, 0.0f,
		Maze->specifications.cellWidth, 0, colour_HEXA, 0.0f, 0.0f);
	SolidCellMesh_Var = AEGfxMeshEnd();
}


void MAZE_DrawMazeCellsandCellOutline2(AEGfxVertexList*& WALLCellMesh,
	AEGfxVertexList*& PATHCellMesh,
	AEGfxVertexList*& CellOutlineMesh,
	Maze_Struct* Maze)
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	for (int r = 0; r < Maze->specifications.noOfRows; r++)
	{
		for (int c = 0; c < Maze->specifications.noOfCols; c++)
		{
			AEGfxSetPosition(
				(Maze->specifications.MazeWindowStart_X + (r * Maze->specifications.cellWidth)),
				(Maze->specifications.MazeWindowStart_Y + (c * Maze->specifications.cellHeight))
			);
			if (Maze->grid[r][c].is_wall == 1) // is wall
			{
				AEGfxMeshDraw(WALLCellMesh, AE_GFX_MDM_TRIANGLES);
			}
			else
			{
				AEGfxMeshDraw(PATHCellMesh, AE_GFX_MDM_TRIANGLES);
			}

			AEGfxSetPosition(
				Maze->specifications.MazeWindowStart_X + (r * Maze->specifications.cellWidth),
				Maze->specifications.MazeWindowStart_Y + (c * Maze->specifications.cellHeight)
			);
			AEGfxMeshDraw(CellOutlineMesh, AE_GFX_MDM_LINES_STRIP);

		}
	}
}


void MAZE_DrawMazeOutline2(AEGfxVertexList*& mazeOutlineMesh, Maze_Struct* Maze)
{
	AEGfxSetPosition(Maze->specifications.MazeWindowStart_X, Maze->specifications.MazeWindowStart_Y);
	AEGfxMeshDraw(mazeOutlineMesh, AE_GFX_MDM_LINES_STRIP);
}


void MAZE_CreateMainCharacter(AEGfxVertexList*& pMesh_MainCharacter, float cell_height, float cell_width)
{
	AEGfxMeshStart();

	//pink: 0x00FF00FF
	//white: 0x00FFFFFF
	//light blue: 0x0000FFFF

	AEGfxTriAdd( //This triangle is colorful, blends 3 colours wowza
		-(cell_width / 4), -(cell_height / 4), 0x00FF00FF, 1.0f, 1.0f, //pink 
		(cell_width / 4), -(cell_height / 4), 0x00FFFFFF, 1.0f, 1.0f, //white
		-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 1.0f, 1.0f); //light blue


	AEGfxTriAdd(
		(cell_width / 4), -(cell_height / 4), 0x00FFFFFF, 1.0f, 1.0f, //white
		(cell_width / 4), (cell_height / 4), 0x00FF00FF, 1.0f, 1.0f, //pink
		-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 1.0f, 1.0f); //light blue

	pMesh_MainCharacter = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh_MainCharacter, "Failed to create main character!!");
}

void MAZE_DrawingMainCharacter(AEGfxVertexList*& pMesh_MainCharacter, float MC_positionX, float MC_positionY)
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(MC_positionX, MC_positionY);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxMeshDraw(pMesh_MainCharacter, AE_GFX_MDM_TRIANGLES);
}

int MAZE_CharMoveCHECK_NEXT_POS(int UpDownLeftRight, Maze_Struct* Maze, int& Char_Pos_X, int& Char_Pos_Y)
{
	switch (UpDownLeftRight)//1 is up, 2 is left, 3 is down, 3 is right
	{
	case 1: // move up aka y+1 
		if (Maze->grid[Char_Pos_X][Char_Pos_Y + 1].is_wall != 1 && (Char_Pos_Y + 1) < Maze->specifications.noOfRows)
		{
			std::cout << "Can move up" << "\n";
			Char_Pos_Y++;
			return 1;
		}
		else
		{
			std::cout << "Cant move up to :" << Char_Pos_X << "-" << Char_Pos_Y + 1
				<< "because :" << Maze->grid[Char_Pos_X][Char_Pos_Y + 1].is_wall << "\n";
			return 0;
		}
		break;
	case 2: // move left aka x-1
		if (Maze->grid[Char_Pos_X - 1][Char_Pos_Y].is_wall != 1 && (Char_Pos_X - 1) >= 0)
		{
			std::cout << "Can move left" << "\n";
			Char_Pos_X--;
			return 1;
		}
		else
		{
			std::cout << "Cant move left to :" << Char_Pos_X - 1 << "-" << Char_Pos_Y
				<< "because :" << Maze->grid[Char_Pos_X - 1][Char_Pos_Y].is_wall << "\n";
			return 0;
		}
		break;
	case 3: // move down aka y-1
		if (Maze->grid[Char_Pos_X][Char_Pos_Y - 1].is_wall != 1 && (Char_Pos_Y - 1) >= 0)
		{
			std::cout << "Can move down" << "\n";
			Char_Pos_Y--;
			return 1;
		}
		else
		{
			std::cout << "Cant move down to :" << Char_Pos_X << "-" << Char_Pos_Y - 1
				<< "because :" << Maze->grid[Char_Pos_X][Char_Pos_Y - 1].is_wall << "\n";
			return 0;
		}
		break;
	case 4: // move right aka x+1
		if (Maze->grid[Char_Pos_X + 1][Char_Pos_Y].is_wall != 1 && (Char_Pos_X + 1) < Maze->specifications.noOfCols)
		{
			std::cout << "Can move right" << "\n";
			Char_Pos_X++;
			return 1;
		}
		else
		{
			std::cout << "Cant move right to :" << Char_Pos_X + 1 << "-" << Char_Pos_Y
				<< "because :" << Maze->grid[Char_Pos_X + 1][Char_Pos_Y].is_wall << "\n";
			return 0;
		}
		break;

	default: return 0;
	}

}


/*
	Loads all assets in Level1. It should only be called once before the start of the level.
	Opens and reads required files, and assigns values to necessary variables.
*/
void Maze_Load()
{
	std::cout << "Maze:Load" << std::endl;

}







/*
	Initializes and sets the starting values of level1.
	Ensures the input file stream opens correctly, and the values
	are assigned accordingly to the variables.
*/
void Maze_Initialize()
{
	std::cout << "Maze:Initialize" << std::endl;
	Maze = CreateMaze(AEGetWindowHeight(), AEGetWindowWidth(), noOfRows, noOfCols);

	MAZE_CreateMESH_MazeWindow2(pMeshMazeWindow, Maze, 0xFF0000);
	MAZE_CreateMESH_CellOutline2(pMeshCellOutline, Maze, 0xFFFFFFFF);
	MAZE_CreateSolidCell2(pMeshSolidSquare_WALL, Maze, 0x000000);
	MAZE_CreateSolidCell2(pMeshSolidSquare_PATH, Maze, 0x808080);
	MAZE_CreateMainCharacter(pMesh_MainCharacter, Maze->specifications.cellHeight, Maze->specifications.cellWidth);

	MC_positionX = Maze->specifications.MazeWindowStart_X + (Maze->specifications.cellWidth / 2) + (starting_Xposition * Maze->specifications.cellWidth);

	MC_positionY = Maze->specifications.MazeWindowStart_Y + (Maze->specifications.cellHeight / 2) + (starting_Yposition * Maze->specifications.cellHeight);
	std::cout << "X : " << MC_positionX << " --- Y : " << MC_positionY << std::endl;
}


/*
	In charge of checking and updating the program.
	Updates every frame. Part of the actual game loop for level1.
	Contols the logic to end or restart the program.
*/
void Maze_Update()
{
	//std::cout << "Maze:Update" << std::endl;

	if (AEInputCheckTriggered(AEVK_W))
	{
		if (MAZE_CharMoveCHECK_NEXT_POS(1, Maze, starting_Xposition, starting_Yposition) == 1)
		{
			MC_positionY += Maze->specifications.cellHeight;
			std::cout << "Current mc XY position " << MC_positionX << "\t\t" << MC_positionY <<
				"\t\t" << starting_Xposition << "\t\t" << starting_Yposition << "\n";
		}
	}

	if (AEInputCheckTriggered(AEVK_S))
	{
		if (MAZE_CharMoveCHECK_NEXT_POS(3, Maze, starting_Xposition, starting_Yposition) == 1)
		{
			MC_positionY -= Maze->specifications.cellHeight;
			std::cout << "Current mc XY position " << MC_positionX << "\t\t" << MC_positionY <<
				"\t\t" << starting_Xposition << "\t\t" << starting_Yposition << "\n";
		}
	}


	if (AEInputCheckTriggered(AEVK_A))
	{
		if (MAZE_CharMoveCHECK_NEXT_POS(2, Maze, starting_Xposition, starting_Yposition) == 1)
		{

			MC_positionX -= Maze->specifications.cellWidth;
			std::cout << "Current mc XY position " << MC_positionX << "\t\t" << MC_positionY <<
				"\t\t" << starting_Xposition << "\t\t" << starting_Yposition << "\n";

		}
	}

	if (AEInputCheckTriggered(AEVK_D))
	{
		if (MAZE_CharMoveCHECK_NEXT_POS(4, Maze, starting_Xposition, starting_Yposition) == 1)
		{

			MC_positionX += Maze->specifications.cellWidth;
			std::cout << "Current mc XY position " << MC_positionX << "\t\t" << MC_positionY <<
				"\t\t" << starting_Xposition << "\t\t" << starting_Yposition << "\n";
		}
	}

}


/*
	Updates every frame together with the update function.
	Draws the updated logic from the update function.
*/
void Maze_Draw()
{
	//std::cout << "Maze:Draw" << std::endl;

	MAZE_DrawMazeCellsandCellOutline2(pMeshSolidSquare_WALL,
		pMeshSolidSquare_PATH,
		pMeshCellOutline,
		Maze
	);



	MAZE_DrawMazeOutline2(pMeshMazeWindow, Maze); //AEGFX MeshDrawMode MDM != AEGFX RenderMode RM
	MAZE_DrawingMainCharacter(pMesh_MainCharacter, MC_positionX, MC_positionY);
}


/*
	Cleans game object instances.
*/
void Maze_Free()
{
	std::cout << "Maze:Free" << std::endl;
	AEGfxMeshFree(pMeshCellOutline);
	AEGfxMeshFree(pMeshMazeWindow);
	AEGfxMeshFree(pMeshSolidSquare_PATH);
	AEGfxMeshFree(pMeshSolidSquare_WALL);
	AEGfxMeshFree(pMesh_MainCharacter);


	delete(Maze);
}


/*
	Unload game assets. Frees and releases memory
*/
void Maze_Unload()
{
	std::cout << "Maze:Unload" << std::endl;
}