modded class ActionDestroyCombinationLock
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!super.ActionCondition(player, target, item))
		{
			return false;
		}

		if (GetGame() && GetGame().IsServer())
		{
			SDN_RaidManagerManager manager = SDN_RaidManagerManager.GetInstance();
			if (manager && manager.IsEnabled() && !manager.IsSDN_RaidManager())
			{
				manager.NotifyPlayerRaidBlocked(player);
				return false;
			}
		}
		// on client, we can't reliably know the raid state without sending RPCs,
		// but since the server blocks it, the action won't complete.
		// Returning true on client allows the prompt to appear, but execution will fail on server.
		return true;
	}
}

// Compatibilidade com mods de CodeLock comuns (ex: CodeLock)
modded class ActionDestroyCodeLock
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!super.ActionCondition(player, target, item))
		{
			return false;
		}

		if (GetGame() && GetGame().IsServer())
		{
			SDN_RaidManagerManager manager = SDN_RaidManagerManager.GetInstance();
			if (manager && manager.IsEnabled() && !manager.IsSDN_RaidManager())
			{
				manager.NotifyPlayerRaidBlocked(player);
				return false;
			}
		}

		return true;
	}
}
