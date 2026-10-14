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
				if (player)
				{
					string message = manager.GetRaidUnavailableMessage();
					if (message != "")
					{
						string playerKey = "unknown";
						PlayerIdentity identity = player.GetIdentity();
						if (identity)
						{
							playerKey = identity.GetPlainId();
						}

						if (manager.CanNotifyPlayer(playerKey))
						{
							player.MessageStatus(message);
						}
					}
				}
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
// Descomente o bloco abaixo (remova /* e */) APENAS SE o seu servidor utilizar
// o mod "CodeLock" original (cuja ação é ActionDestroyCodeLock).
// Caso contrário, o servidor não compilará informando "Unknown type".

/*
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
				if (player)
				{
					string message = manager.GetRaidUnavailableMessage();
					if (message != "")
					{
						string playerKey = "unknown";
						PlayerIdentity identity = player.GetIdentity();
						if (identity)
						{
							playerKey = identity.GetPlainId();
						}

						if (manager.CanNotifyPlayer(playerKey))
						{
							player.MessageStatus(message);
						}
					}
				}
				return false;
			}
		}

		return true;
	}
}
*/
