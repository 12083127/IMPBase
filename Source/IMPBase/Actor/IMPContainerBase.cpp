// IMP Project - Robert Lehmann 2020-2021


#include "IMPContainerBase.h"
#include "IMPBase/Components/IMPInventoryComponent.h"

AIMPContainerBase::AIMPContainerBase()
{
	DisplayName = FText::FromString("Container");
	Inventory = CreateDefaultSubobject<UIMPInventoryComponent>(TEXT("ContainerInventory"));
}