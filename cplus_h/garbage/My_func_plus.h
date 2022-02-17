#pragma once
//
////最大値求める
//template <class Type>
//Type get_max(Type* data, int size);
//
////最小値求める
//template <class Type>
//Type get_min(Type* data, int size);
//
////最大値で正規化,double型出力
//template <class Type>
//void norm_max(Type* data_in, int size, double* data_out);
//
////最大値と最小値で正規化(確実に0~1),double型出力
//template <class Type>
//void norm_max_min(Type* data_in, int size, double* data_out);
//
////正規化後,n階調化,int型出力
//template <class Type>
//void norm_reso_n(Type* data_in, int* data_out, int n, int size);
//
//
////intデータをunsigned charに変換後、格納
////0~255のデータに限る
//void to_uch(int* data_in, int size, unsigned char* data_img);
//
//
////1次元画像の上下反転
//template <class Type>
//void invert_img(Type* data_in, Type* data_out, int im_x, int im_y);
//
////中心1列取り出す
//template <class Type>
//void mid_line(Type* data_in, int sx, int sy, Type* data_out);
//
//
////実行者に強制二択
////cfがに値が入る、oneは選択肢１の名称、the_otherは２の名称、valueは選択肢を選ぶとき入力させる数字
//void forced_two_select(int* cf, char one[], char the_other[], int one_value, int other_value);
//
//
//
////実行者に強制二択
////返却値に値が入る、oneは選択肢１の名称、the_otherは２の名称、valueは選択肢を選ぶとき入力させる数字
//int forced_two_select_ver2(char title[] ,char one[], char the_other[], int one_value, int other_value);

//最大値
template <class Type>
inline Type get_max(Type* data, int size)
{
	Type max = data[0];
	for (int i = 0; i < size; i++) {
		if (max < data[i]) {
			max = data[i];
		}
	}

	return max;
}

//最小値
template <class Type>
inline Type get_min(Type* data, int size)
{
	Type min = data[0];
	for (int i = 0; i < size; i++) {
		if (min > data[i]) {
			min = data[i];
		}
	}

	return min;
}

//最大値で正規化
template <class Type>
inline void norm_max(Type* data_in, int size, double* data_out)
{
	Type max;
	max = get_max(data_in, size);

	for (int i = 0; i < size; i++) {
		data_out[i] = (double)((double)data_in[i] / (double)max);
	}

}

//最大値と最小値で正規化(確実に0~1)
template <class Type>
inline void norm_max_min(Type* data_in, int size, double* data_out)
{
	Type max;
	max = get_max(data_in, size);
	Type min;
	min = get_min(data_in, size);

	double* tmp;
	tmp = new double[size];

	for (int i = 0; i < size; i++) {
		tmp[i] = (double)((data_in[i] - min) / (max - min));
	}

	for (int i = 0; i < size; i++) {
		data_out[i] = tmp[i];
	}


	delete[]tmp;
}

//正規化後,n階調化,int型出力
template <class Type>
inline void norm_reso_n(Type* data_in, int* data_out, int n, int size)
{
	double* tmp;
	tmp = new double[size];
	norm_max_min(data_in, size, tmp);

	for (int i = 0; i < size; i++) {
		data_out[i] = (int)(round(tmp[i] * n));
	}

	delete[]tmp;
}


//intデータをunsigned charに変換後、格納
//0~255のデータに限る
inline void to_uch(int* data_in, int size, unsigned char* data_img)
{
	for (int i = 0; i < size; i++) {
		data_img[i] = (unsigned char)data_in[i];
	}
}


//1次元画像の上下反転
template <class Type>
inline void invert_img(Type* data_in, Type* data_out, int im_x, int im_y)
{
	Type* tmp;
	tmp = new Type[im_x * im_y];

	for (int i = 0; i < im_y; i++) {
		for (int j = 0; j < im_x; j++) {
			tmp[i * im_x + j] = data_in[((im_y - 1) - i) * im_x + j];

		}
	}

	for (int i = 0; i < im_y; i++) {
		for (int j = 0; j < im_x; j++) {
			data_out[i * im_x + j] = tmp[i * im_x + j];

		}
	}



	delete[]tmp;
}


//中心1列取り出す
template <class Type>
inline void mid_line(Type* data_in, int sx, int sy, Type* data_out) {
	for (int i = 0; i < sx; i++) {
		data_out[i] = data_in[(sy / 2) * sx + i];
	}
}

//
////実行者に強制二択
////cfがに値が入る、oneは選択肢１の名称、the_otherは２の名称、valueは選択肢を選ぶとき入力させる数字
//void forced_two_select(int* cf, char one[], char the_other[], int one_value, int other_value) {
//
//	do {
//		printf("\n%s：%dを入力\t%s：%dを入力\n", one, one_value, the_other, other_value);
//		printf("Press 0 or 1 and enterkey : "); (void)scanf("%d", cf);
//	} while (*cf != one_value && *cf != other_value);
//}
//
////実行者に強制二択
////返却値に値が入る、oneは選択肢１の名称、the_otherは２の名称、valueは選択肢を選ぶとき入力させる数字
//int forced_two_select_ver2(char title[], char one[], char the_other[], int one_value, int other_value) {
//	int res = 0;
//	do {
//		printf("\n%s\n%s：%dを入力\t%s：%dを入力\n", title, one, one_value, the_other, other_value);
//		printf("Press 0 or 1 and enterkey : "); (void)scanf("%d", &res);
//	} while (res != one_value && res != other_value);
//	return res;
//}