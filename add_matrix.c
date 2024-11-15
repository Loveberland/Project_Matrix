#include <stdio.h>
#include <stdlib.h>

// ฟังก์ชันสำหรับรับจำนวนแถวและคอลัมน์ รวมทั้งค่าของเมทริกซ์ A และ B
void get_number(int **matA, int **matB, int *row, int *col) {
    // ขอจำนวนแถวและคอลัมน์ของเมทริกซ์จากผู้ใช้
    printf("จำนวนแถว: ");
    scanf("%d", row);  // อ่านจำนวนแถว
    printf("จำนวนคอลัมน์: ");
    scanf("%d", col);  // อ่านจำนวนคอลัมน์

    // จองหน่วยความจำสำหรับทั้งเมทริกซ์ A และ B ในบล็อกเดียวกัน
    // เพราะเมทริกซ์เป็นแบบ 2D เราจึงจองเป็นอาเรย์ 1D ขนาด row*col
    *matA = malloc((*row) * (*col) * sizeof(int));  // จองหน่วยความจำสำหรับเมทริกซ์ A
    *matB = malloc((*row) * (*col) * sizeof(int));  // จองหน่วยความจำสำหรับเมทริกซ์ B

    // รับค่าของเมทริกซ์ A
    printf("\nกรอกค่าให้กับ Matrix A:\n");
    for(int i = 0; i < (*row) * (*col); i++) {
        scanf("%d", (*matA) + i);  // ใช้ pointer arithmetic เพื่อกรอกค่าทุกตัว
    }

    // รับค่าของเมทริกซ์ B
    printf("\nกรอกค่าให้กับ Matrix B:\n");
    for(int i = 0; i < (*row) * (*col); i++) {
        scanf("%d", (*matB) + i);  // ใช้ pointer arithmetic เพื่อกรอกค่าทุกตัว
    }
}

// ฟังก์ชันสำหรับการบวกเมทริกซ์ A และ B และแสดงผลลัพธ์
void add_and_print(int *matA, int *matB, int row, int col) {
    // จองหน่วยความจำสำหรับเมทริกซ์ผลลัพธ์ (สำหรับเก็บผลลัพธ์การบวก)
    int *summat = malloc(row * col * sizeof(int));

    // คำนวณผลลัพธ์ของการบวกเมทริกซ์ A และ B และแสดงผลในลูปเดียว
    printf("\nSum Matrix:\n");
    for(int i = 0; i < row * col; i++) {
        // บวกค่าของเมทริกซ์ A และ B แล้วเก็บผลลัพธ์ใน summat
        summat[i] = matA[i] + matB[i];

        // แสดงผลลัพธ์การบวก และตามด้วยช่องว่าง
        printf("%d ", summat[i]);

        // ถ้าตัวเลขปัจจุบันเป็นตัวสุดท้ายของแถว ให้พิมพ์บรรทัดใหม่
        if ((i + 1) % col == 0) {
            printf("\n");
        }
    }

    // ฟรีหน่วยความจำที่จองไว้สำหรับเมทริกซ์ผลลัพธ์ เพราะไม่จำเป็นต้องใช้แล้ว
    free(summat);
}

int main() {
    int *matA, *matB;  // พอยน์เตอร์สำหรับเก็บที่อยู่ของเมทริกซ์ A และ B
    int row, col;      // ตัวแปรเก็บจำนวนแถวและคอลัมน์

    // เรียกฟังก์ชัน get_number เพื่อรับค่าขนาดและข้อมูลของเมทริกซ์
    get_number(&matA, &matB, &row, &col);

    // เรียกฟังก์ชัน add_and_print เพื่อบวกเมทริกซ์และแสดงผล
    add_and_print(matA, matB, row, col);

    // ฟรีหน่วยความจำที่จองไว้สำหรับเมทริกซ์ A และ B
    free(matA);
    free(matB);

    return 0;
}

