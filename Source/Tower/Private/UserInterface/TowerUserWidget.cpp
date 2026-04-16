// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "UserInterface/TowerUserWidget.h"

void UTowerUserWidget::SetWidgetController(UObject* InWidgetController)
{
	if (IsValid(InWidgetController))
	{
		WidgetController = InWidgetController;
		WidgetControllerSet();
	}
}
