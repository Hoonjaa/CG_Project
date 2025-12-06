#include "pch.h"
#include "Random.h"
#include "Player.h"
#include "Cube.h"
#include "Bullet.h"
#include "Room.h"
#include "Ground.h"
#include "Zombie.h"
#include "Minimap.h"

//--- 아래 5개 함수는 사용자 정의 함수임
void make_vertexShaders();
void make_fragmentShaders();
GLuint make_shaderProgram();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
// 키보드 이벤트 처리 함수
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid KeyboardUp(unsigned char key, int x, int y);
GLvoid SpecialKeyboard(int key, int x, int y);
// 마우스 이벤트 처리 함수
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);
GLvoid PassiveMotion(int x, int y); // 추가: 마우스 버튼을 누르지 않은 상태에서의 움직임
GLvoid Win_to_GL_mouse(int x, int y, GLfloat& gl_x, GLfloat& gl_y);
// 타이머 함수
GLvoid TimerFunction(int value);

// --------------여기부터 필요한 함수들 선언하는 구역-------------
// 뷰 및 투영 변환 행렬
GLvoid setViewPerspectiveMatrix();
glm::mat4 getViewPerspectiveMatrix();
glm::mat4 getThirdPersonViewMatrix();
// 변환 행렬 업데이트
GLvoid updateTransformMatrix();
// 좀비 생성 함수
GLvoid spawnZombie();
// 텍스트 렌더링 함수
GLvoid renderText(float x, float y, const char* text);
// 1인칭/3인칭 전환 함수
GLvoid toggleViewMode();



//--- 필요한 변수 선언
GLuint shaderProgramID;													//--- 세이더 프로그램 이름
GLuint vertexShader;													//--- 버텍스 세이더 객체
GLuint fragmentShader;													//--- 프래그먼트 세이더 객체

// --------------여기부터 필요한 변수들 선언하는 구역-------------

GLint WindowWidth = 800, WindowHeight = 800;
bool Timer = true; // 타이머 사용중
glm::mat4 Transform_matrix{ 1.0f };

// 플레이어 이동
bool key_w = false;
bool key_a = false;
bool key_s = false;
bool key_d = false;

// 플레이어 바라보는 방향 관련 변수
int centerX = 410, centerY = 400; // 화면 중앙 좌표
bool firstMouse = true;
bool mouseWarped = false; // 마우스가 강제로 이동했는지 체크하는 플래그

// 좀비 생성 관련 변수
int frameCount = 0;                    // 프레임 카운터
const int SPAWN_INTERVAL = 180;        // 스폰 간격 (180프레임 = 약 3초, 60fps 기준)
const int MAX_ZOMBIES = 20;            // 최대 좀비 수

//Cube* cube = nullptr; 예시임 포인터로 객체 선언
// 포인터로 하는 이유는 셰이더가 만들어지는 등 기본 세팅 코드가 먼저 작동해야 객체 생성가능
// 따라서 main 함수 안에서 new로 객체 생성
Player* player = nullptr;
Cube* cube = nullptr;
Room* room = nullptr;
Ground* ground = nullptr;
std::vector<Bullet*> bullets;
std::vector<Zombie*> zombies;
Minimap* minimap = nullptr;

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb");											// Open file for reading
	if (!fptr)															// Return NULL on failure
		return NULL;
	fseek(fptr, 0, SEEK_END);											// Seek to the end of the file
	length = ftell(fptr);												// Find out how many bytes into the file we are
	buf = (char*)malloc(length + 1);									// Allocate a buffer for the entire length of the file and a null terminator
	fseek(fptr, 0, SEEK_SET);											// Go back to the beginning of the file
	fread(buf, length, 1, fptr);										// Read the contents of the file in to the buffer
	fclose(fptr);														// Close the file
	buf[length] = 0;													// Null terminator
	return buf;															// Return the buffer
}
//--- 메인 함수
void main(int argc, char** argv)										//--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow("Example1");
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();
	//--- 세이더 읽어와서 세이더 프로그램 만들기: 사용자 정의함수 호출
	make_vertexShaders();												//--- 버텍스 세이더 만들기
	make_fragmentShaders();												//--- 프래그먼트 세이더 만들기
	shaderProgramID = make_shaderProgram();
	//--- 세이더 프로그램 만들기
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);


	// --------------기본 객체 생성 시 여기서 작업-------------
	// cube = new Cube(); 이런식
	player = new Player();
	player->setup(shaderProgramID);
	cube = new Cube();
	room = new Room();
	ground = new Ground();
	minimap = new Minimap(shaderProgramID);
	minimap->setWorldSize(40.0f);


	toggleViewMode(); // 초기 뷰 모드 설정
	glutTimerFunc(16, TimerFunction, 1);
	setViewPerspectiveMatrix();
	glutDisplayFunc(drawScene);											//--- 출력 콜백 함수
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialFunc(SpecialKeyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutPassiveMotionFunc(PassiveMotion); // 추가: 마우스 버튼을 누르지 않은 상태에서의 움직임 감지
	glutMainLoop();
}

//--- 버텍스 세이더 객체 만들기
void make_vertexShaders()
{
	GLchar* vertexSource;
	//--- 버텍스 세이더 읽어 저장하고 컴파일 하기
	//--- filetobuf: 사용자정의 함수로 텍스트를 읽어서 문자열에 저장하는 함수
	vertexSource = filetobuf("vertex.glsl");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

//--- 프래그먼트 세이더 객체 만들기
void make_fragmentShaders()
{
	GLchar* fragmentSource;
	//--- 프래그먼트 세이더 읽어 저장하고 컴파일하기
	fragmentSource = filetobuf("fragment.glsl");						// 프래그세이더 읽어오기
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: frag_shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

//--- 세이더 프로그램 만들고 세이더 객체 링크하기
GLuint make_shaderProgram()
{
	GLint result;
	GLchar* errorLog = NULL;
	GLuint shaderID;
	shaderID = glCreateProgram();										//--- 세이더 프로그램 만들기
	glAttachShader(shaderID, vertexShader);								//--- 세이더 프로그램에 버텍스 세이더 붙이기
	glAttachShader(shaderID, fragmentShader);							//--- 세이더 프로그램에 프래그먼트 세이더 붙이기
	glLinkProgram(shaderID);											//--- 세이더 프로그램 링크하기
	glDeleteShader(vertexShader);										//--- 세이더 객체를 세이더 프로그램에 링크했음으로, 세이더 객체 자체는 삭제 가능
	glDeleteShader(fragmentShader);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);					// ---세이더가 잘 연결되었는지 체크하기
	if (!result) {
		glGetProgramInfoLog(shaderID, 512, NULL, errorLog);
		std::cerr << "ERROR: shader program 연결 실패\n" << errorLog << std::endl;
		return false;
	}
	glUseProgram(shaderID);												//--- 만들어진 세이더 프로그램 사용하기
	//--- 여러 개의 세이더프로그램 만들 수 있고, 그 중 한개의 프로그램을 사용하려면
	//--- glUseProgram 함수를 호출하여 사용 할 특정 프로그램을 지정한다.
	//--- 사용하기 직전에 호출할 수 있다.
	return shaderID;
}

//--- 출력 콜백 함수
GLvoid drawScene()														//--- 콜백 함수: 그리기 콜백 함수
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgramID);
	glPointSize(5.0);

	// 이 model 같은 경우엔 프래그먼트 셰이더에서 조명 계산할 때 필요함
	// 뷰, 투영 제외한 월드 좌표계만 변환 행렬한거임
	// 일단은 단위 행렬로 설정해야 해서 이렇게 둘거임
	// 추후에 객체의 draw함수에서 별도로 설정해줄 것
	// 설정이 끝나면 아래 3줄 코드는 삭제해도 무방함.


	// 조명 관련 uniform 변수들 설정
	unsigned int lightPosLocation = glGetUniformLocation(shaderProgramID, "lightPos"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
	glUniform3f(lightPosLocation, 0.0f, 10.0f, 0.0f);
	unsigned int lightColorLocation = glGetUniformLocation(shaderProgramID, "lightColor"); //--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
	glUniform3f(lightColorLocation, 1.0f, 1.0f, 1.0f);

	// ----------------여기서 객체 그리기--------------------
	// cube->draw(shaderProgramID, Transform_matrix); 이런식
	// cube 내부에서 유니폼 변수를 바꿔주기 위해 shaderProgramID 전달
	// cube 내부에서 최종 변환 행렬을 설정해야하기 때문에 Transform_matrix 전달
	// 현재 Transform_matrix는 뷰 및 투영 변환 행렬임

	// 결과적으론 cube->draw(shaderProgramID, Transform_matrix); 함수 하나 만으로 애니메이션까지 다 처리 가능하게
	glm::mat4 viewMatrix;
	glm::vec3 viewPos;

	if (player && player->isFirstPersonMode()) {
		viewMatrix = player->getFirstPersonViewMatrix();
		viewPos = player->getPosition() + glm::vec3(0.0f, 0.7f, 0.0f); // 카메라 위치 (조명용임 실제로 바꾸는건 Player_body로)
	}
	else {
		viewMatrix = getThirdPersonViewMatrix();
		viewPos = glm::vec3(0.0f, 10.0f, 20.0f);
	}

	// viewPos uniform 설정
	unsigned int viewPosLocation = glGetUniformLocation(shaderProgramID, "viewPos");
	glUniform3f(viewPosLocation, viewPos.x, viewPos.y, viewPos.z);

	// 투영 행렬
	glm::mat4 projection = glm::perspective(glm::radians(70.0f), 1.0f, 0.1f, 100.0f);
	glm::mat4 viewProjectionMatrix = projection * viewMatrix;

	player->render(viewProjectionMatrix);
	cube->draw(shaderProgramID, glm::mat4(1.0f), viewProjectionMatrix);
	room->draw(shaderProgramID, glm::mat4(1.0f), viewProjectionMatrix);
	ground->draw(shaderProgramID, glm::mat4(1.0f), viewProjectionMatrix);

	for (auto* bullet : bullets) {
		if (bullet) {
			bullet->draw(shaderProgramID, glm::mat4(1.0f), viewProjectionMatrix);
		}
	}

	for (auto zombie : zombies) {
		if (zombie) {
			zombie->render(viewProjectionMatrix);
		}
	}

	// 디버그: 바운딩 박스 그리기
	glUseProgram(0); // 셰이더 비활성화
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(projection));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(viewMatrix));
	
	// 좀비 바운딩 박스
	for (auto zombie : zombies) {
		if (zombie) {
			zombie->get_bb().drawDebug();
		}
	}
	
	// 총알 바운딩 박스
	for (auto* bullet : bullets) {
		if (bullet) {
			bullet->get_bb().drawDebug();
		}
	}
	
	glUseProgram(shaderProgramID); // 셰이더 다시 활성화

	if (minimap) {
		minimap->render(player->getPosition(), zombies);
	}

	// ============= UI 렌더링 시작 =============
	// 셰이더 프로그램 비활성화
	glUseProgram(0);
	
	// 투영 및 모델뷰 행렬을 2D 모드로 전환
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WindowWidth, 0, WindowHeight);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// 깊이 테스트 비활성화
	glDisable(GL_DEPTH_TEST);

	// 탄약 정보 배경 박스
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glColor4f(0.0f, 0.0f, 0.0f, 0.7f); // 반투명 검은색 배경
	glBegin(GL_QUADS);
		glVertex2f(WindowWidth - 170, 15);
		glVertex2f(WindowWidth - 10, 15);
		glVertex2f(WindowWidth - 10, player && player->is_reloading ? 85 : 55);
		glVertex2f(WindowWidth - 170, player && player->is_reloading ? 85 : 55);
	glEnd();
	
	glDisable(GL_BLEND);

	// 탄약 정보 표시
	if (player) {
		char ammoText[50];
		sprintf_s(ammoText, "Ammo: %d / 30", player->bulletCount);

		// 텍스트 색상 (밝은 녹색)
		glColor3f(0.0f, 1.0f, 0.0f);
		
		glRasterPos2f(WindowWidth - 155, 30);
		for (char* c = ammoText; *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		}

		// 재장전 중이면 표시
		if (player->is_reloading) {
			glColor3f(1.0f, 1.0f, 0.0f); // 노란색
			glRasterPos2f(WindowWidth - 155, 60);
			const char* reloadText = "Reloading...";
			for (const char* c = reloadText; *c != '\0'; c++) {
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
			}
		}
	}

	// 좀비 수 배경 박스
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
	glBegin(GL_QUADS);
		glVertex2f(WindowWidth - 160, WindowHeight - 50);
		glVertex2f(WindowWidth - 10, WindowHeight - 50);
		glVertex2f(WindowWidth - 10, WindowHeight - 10);
		glVertex2f(WindowWidth - 160, WindowHeight - 10);
	glEnd();
	
	glDisable(GL_BLEND);

	// 좀비 수 표시
	char zombieText[50];
	sprintf_s(zombieText, "Zombies: %d / %d", (int)zombies.size(), MAX_ZOMBIES);
	glColor3f(1.0f, 0.0f, 0.0f); // 빨간색
	glRasterPos2f(WindowWidth - 150, WindowHeight - 30);
	for (char* c = zombieText; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}

	// 깊이 테스트 다시 활성화
	glEnable(GL_DEPTH_TEST);

	// 행렬 복원
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
	// 셰이더 프로그램 다시 활성화
	glUseProgram(shaderProgramID);

	glutSwapBuffers();
}
//--- 다시그리기 콜백 함수
GLvoid Reshape(int w, int h)											//--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
	WindowWidth = w;
	WindowHeight = h;
	centerX = w / 2 + 10;
	centerY = h / 2;
}

GLvoid Motion(int x, int y) {
	// 마우스가 강제로 이동된 경우 무시
	if (mouseWarped) {
		mouseWarped = false;
		return;
	}

	if (firstMouse) {
		firstMouse = false;
		return;
	}

	// 1인칭 모드에서만 처리
	if (player && player->isFirstPersonMode()) {

		float deltaX = x - centerX;
		float deltaY = y - centerY;

		// 델타가 너무 작으면 무시 (노이즈 제거)
		if (abs(deltaX) < 1 && abs(deltaY) < 1) {
			return;
		}

		player->handleMouseMovement(deltaX, deltaY);

		// 마우스를 화면 중앙으로 다시 이동
		mouseWarped = true;
		glutWarpPointer(centerX, centerY);
		glutPostRedisplay();
	}
	glutPostRedisplay();
}

GLvoid PassiveMotion(int x, int y) {
	// 마우스가 강제로 이동된 경우 무시
	if (mouseWarped) {
		mouseWarped = false;
		return;
	}

	if (firstMouse) {
		firstMouse = false;
		return;
	}

	// 1인칭 모드에서만 처리
	if (player && player->isFirstPersonMode()) {
		float deltaX = x - centerX;
		float deltaY = y - centerY;

		// 델타가 너무 작으면 무시 (노이즈 제거)
		if (abs(deltaX) < 1 && abs(deltaY) < 1) {
			return;
		}

		player->handleMouseMovement(deltaX, deltaY);

		// 마우스를 화면 중앙으로 다시 이동
		mouseWarped = true;
		glutWarpPointer(centerX, centerY);
		glutPostRedisplay();
	}
}

GLvoid Mouse(int button, int state, int x, int y) {
	GLfloat gl_x, gl_y;
	Win_to_GL_mouse(x, y, gl_x, gl_y);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (player && player->canFire && player->bulletCount > 0) {
			// 총구 위치에서 총알 생성
			glm::vec3 muzzlePos = player->getMuzzlePosition();
			glm::vec3 fireDir = player->getFireDirection();

			// 총알 생성
			Bullet* newBullet = new Bullet(muzzlePos, player->getFireDirection());
			bullets.push_back(newBullet);

			// 총알 수 감소
			player->bulletCount--;

			std::cout << "총알 발사! 남은 총알: " << player->bulletCount << std::endl;
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {

	}
	glutPostRedisplay();
}

GLvoid Win_to_GL_mouse(int x, int y, GLfloat& gl_x, GLfloat& gl_y) {
	gl_x = (x / (float)WindowWidth) * 2.0f - 1.0f;
	gl_y = 1.0f - (y / (float)WindowHeight) * 2.0f;
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
		glutLeaveMainLoop();
		break;
	case 'h':
		if (glIsEnabled(GL_DEPTH_TEST))
			glDisable(GL_DEPTH_TEST);
		else
			glEnable(GL_DEPTH_TEST);
		break;
	case 'u':
		if (glIsEnabled(GL_CULL_FACE))
			glDisable(GL_CULL_FACE);
		else
			glEnable(GL_CULL_FACE);
		break;
	case 'c':
		//if (player) {
		//	player->toggleViewMode();
		//	// 1인칭 모드로 전환할 때 마우스를 중앙에 위치
		//	if (player->isFirstPersonMode()) {
		//		glutSetCursor(GLUT_CURSOR_CROSSHAIR);
		//		glutWarpPointer(centerX, centerY);
		//		firstMouse = true;
		//		mouseWarped = true;
		//	}
		//}
		break;
	case 'w':
		key_w = true;
		break;
	case 'a':
		key_a = true;
		break;
	case 's':
		key_s = true;
		break;
	case 'd':
		key_d = true;
		break;
	case 'r':
		if (player) {
			player->is_reloading = true;
		}
		break;
	}
	glutPostRedisplay();
}

GLvoid KeyboardUp(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		key_w = false;
		break;
	case 'a':
		key_a = false;
		break;
	case 's':
		key_s = false;
		break;
	case 'd':
		key_d = false;
		break;
	}
	glutPostRedisplay();
}

GLvoid SpecialKeyboard(int key, int x, int y)
{
	switch (key) {
	
	}
	glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	//좀비
	// 프레임 카운터 증가
	frameCount++;

	// 일정 간격마다 새로운 좀비 생성
	if (frameCount >= SPAWN_INTERVAL) {
		spawnZombie();
		frameCount = 0;  // 카운터 리셋
	}

	// 모든 좀비 업데이트
	for (auto zombie : zombies) {
		if (zombie) {
			zombie->Walk(player->getPosition());
		}
	}

	//플레이어
	if (player) {
		player->processMovement(key_w, key_a, key_s, key_d);
		player->reload();
	}
	
	// 총알 업데이트 및 충돌 체크
	for (int i = bullets.size() - 1; i >= 0; i--) {
		if (bullets[i]) {
			bullets[i]->update();

			// 생명주기가 끝난 총알 삭제
			if (bullets[i]->Destroy()) {
				delete bullets[i];
				bullets.erase(bullets.begin() + i);
				continue;
			}
			
			// 총알과 좀비의 충돌 체크
			bool bulletHit = false;
			BoundingBox bulletBB = bullets[i]->get_bb();
			
			for (int j = zombies.size() - 1; j >= 0; j--) {
				if (zombies[j]) {
					BoundingBox zombieBB = zombies[j]->get_bb();
					
					
					if (bulletBB.intersects(zombieBB)) {
						std::cout << "=== 충돌 감지! ===" << std::endl;
						// 충돌 발생 - 좀비 삭제
						delete zombies[j];
						zombies.erase(zombies.begin() + j);
						bulletHit = true;
						std::cout << "좀비 처치! 남은 좀비 수: " << zombies.size() << std::endl;
						break;
					}
				}
			}
			
			// 충돌한 총알 삭제
			if (bulletHit) {
				delete bullets[i];
				bullets.erase(bullets.begin() + i);
			}
		}
	}
	
	glutPostRedisplay();
	if (Timer) {
		glutTimerFunc(16, TimerFunction, 1);
	}
}

GLvoid setViewPerspectiveMatrix() {
	glm::vec3 eye = glm::vec3(0.0f, 10.0f, 20.0f);
	unsigned int viewPosLocation = glGetUniformLocation(shaderProgramID, "viewPos");
	glUniform3f(viewPosLocation, eye.x, eye.y, eye.z);

	glm::mat4 view = glm::lookAt(eye,
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

	Transform_matrix = projection * view;
	updateTransformMatrix();
}

glm::mat4 getViewPerspectiveMatrix() {
	glm::vec3 eye = glm::vec3(0.0f, 10.0f, 20.0f);
	unsigned int viewPosLocation = glGetUniformLocation(shaderProgramID, "viewPos");
	glUniform3f(viewPosLocation, eye.x, eye.y, eye.z);

	glm::mat4 view = glm::lookAt(eye,
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

	return projection * view;
}

GLvoid updateTransformMatrix() {
	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "Transform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Transform_matrix));
}

glm::mat4 getThirdPersonViewMatrix() {
	glm::vec3 eye = glm::vec3(0.0f, 10.0f, 20.0f);
	glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	return glm::lookAt(eye, center, up);
}

GLvoid spawnZombie() {
	if (zombies.size() >= MAX_ZOMBIES) {
		return;  // 최대 좀비 수에 도달하면 생성하지 않음
	}

	glm::vec3 randomPos = getRandomZombieSpawnPosition();
	Zombie* newZombie = new Zombie(randomPos);
	newZombie->setup(shaderProgramID);
	zombies.push_back(newZombie);

	std::cout << "좀비 생성, 위치: (" << randomPos.x << ", " << randomPos.y << ", " << randomPos.z
		<< "), 현재 좀비 수: " << zombies.size() << std::endl;
}

GLvoid toggleViewMode() {
	if (player) {
		player->toggleViewMode();
		// 1인칭 모드로 전환할 때 마우스를 중앙에 위치
		if (player->isFirstPersonMode()) {
			glutSetCursor(GLUT_CURSOR_CROSSHAIR);
			glutWarpPointer(centerX, centerY);
			firstMouse = true;
			mouseWarped = true;
		}
	}
}