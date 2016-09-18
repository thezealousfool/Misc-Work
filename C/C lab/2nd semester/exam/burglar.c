#include <stdio.h>
#include <stdlib.h>

struct artifact{
    int artifact_number;
    float weight, price, price_by_weight;
};

void sort_artifacts (struct artifact *object, int number_artifact) {
    // performing bubble sort
    // sorting in the decreasing order of the price/weight value
    int index1, index2;
    struct artifact temp;
    for (index1=0; index1<number_artifact; ++index1) {
        for (index2=0; index2<number_artifact-1; ++index2) {
            if (object[index2+1].price_by_weight > object[index2].price_by_weight) {
                temp = object[index2];
                object[index2] = object[index1];
                object[index1] = temp;
            }
        }
    }
}

int main() {
    float capacity_bag;
    int number_artifact, artifact_index, artifacts_checked;
    struct artifact *object;
    printf("Enter capacity of bag: ");
    scanf("%f", &capacity_bag);
    printf("Enter number of artifacts: ");
    scanf("%d", &number_artifact);
    object=malloc(number_artifact*sizeof(struct artifact));
    for (artifact_index=0; artifact_index<number_artifact; ++artifact_index) {
        printf("Enter artifact %d weight and price: ", artifact_index+1);
        object[artifact_index].artifact_number = artifact_index + 1;
        scanf("%f, %f", &object[artifact_index].weight, &object[artifact_index].price);
        object[artifact_index].price_by_weight = object[artifact_index].price / object[artifact_index].weight;
    }
    sort_artifacts(object, number_artifact);
    artifacts_checked = 0;
    printf("Take artifact ");
    while (capacity_bag>0 && artifacts_checked<number_artifact) {
        if (object[artifacts_checked].weight <= capacity_bag) {
            printf("%d ", object[artifacts_checked].artifact_number);
            capacity_bag -= object[artifacts_checked].weight;
        }
        ++artifacts_checked;
    }
    printf("\n");
}