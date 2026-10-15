modded class ActionDestroyCombinationLock
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!super.ActionCondition(player, target, item))
		{
			return false;
		}

		SDN_RaidManagerManager manager = SDN_RaidManagerManager.GetInstance();
		if (!manager)
			return true;

		if (GetGame() && GetGame().IsServer())
		{
			if (manager.IsEnabled() && !manager.IsSDN_RaidManager())
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
		else if (GetGame() && GetGame().IsClient())
		{
			// No cliente, checamos o estado que foi sincronizado via RPC
			if (!manager.GetClientRaidActive())
			{
				return false; // Esconde a opção se o raid não estiver ativo
			}
		}

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
