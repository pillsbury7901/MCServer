
// RankManager.h

// Declares the cRankManager class that represents the rank manager responsible for assigning permissions and message visuals to players




#pragma once

#include "SQLiteCpp/Database.h"





class cRankManager
{
public:
	cRankManager(void);
	
	/** Returns the name of the rank that the specified player has assigned to them. */
	AString GetPlayerRankName(const AString & a_PlayerUUID);
	
	/** Returns the names of Groups that the specified player has assigned to them. */
	AStringVector GetPlayerGroups(const AString & a_PlayerUUID);
	
	/** Returns the permissions that the specified player has assigned to them. */
	AStringVector GetPlayerPermissions(const AString & a_PlayerUUID);
	
	/** Returns the names of groups that the specified rank has assigned to it. */
	AStringVector GetRankGroups(const AString & a_RankName);
	
	/** Returns the permissions that the specified group has assigned to it. */
	AStringVector GetGroupPermissions(const AString & a_GroupName);
	
	/** Returns all permissions that the specified rank has assigned to it, through all its groups. */
	AStringVector GetRankPermissions(const AString & a_RankName);
	
	/** Returns the names of all defined ranks. */
	AStringVector GetAllRanks(void);
	
	/** Returns the names of all permission groups. */
	AStringVector GetAllGroups(void);
	
	/** Returns all the distinct permissions that are stored in the DB. */
	AStringVector GetAllPermissions(void);
	
	/** Returns the message visuals (prefix, postfix, color) for the specified player. */
	void GetPlayerMsgVisuals(
		const AString & a_PlayerUUID,
		AString & a_MsgPrefix,
		AString & a_MsgSuffix,
		AString & a_MsgNameColorCode
	);
	
	/** Adds a new rank. No action if the rank already exists. */
	void AddRank(
		const AString & a_RankName,
		const AString & a_MsgPrefix,
		const AString & a_MsgSuffix,
		const AString & a_MsgNameColorCode
	);
	
	/** Adds a new permission group. No action if such a group already exists. */
	void AddGroup(const AString & a_GroupName);
	
	/** Adds the specified permission group to the specified rank.
	Fails if the rank or group names are not found.
	Returns true if successful, false on error. */
	bool AddGroupToRank(const AString & a_RankName, const AString & a_GroupName);
	
	/** Adds the specified permission to the specified permission group.
	Fails if the permission group name is not found.
	Returns true if successful, false on error. */
	bool AddPermissionToGroup(const AString & a_Permission, const AString & a_GroupName);
	
	/** Removes the specified rank.
	All players assigned to that rank will be re-assigned to a_ReplacementRankName, unless it is empty. */
	void RemoveRank(const AString & a_RankName, const AString & a_ReplacementRankName);
	
	/** Removes the specified group completely.
	The group will first be removed from all ranks using it, and then removed itself. */
	void RemoveGroup(const AString & a_GroupName);
	
	/** Removes the specified group from the specified rank.
	The group will stay defined, even if no rank is using it. */
	void RemoveGroupFromRank(const AString & a_RankName, const AString & a_GroupName);
	
	/** Removes the specified permission from the specified group. */
	void RemovePermissionFromGroup(const AString & a_Permission, const AString & a_GroupName);
	
	/** Renames the specified rank. No action if the rank name is not found.
	Fails if the new name is already used.
	Returns true on success, false on failure. */
	bool RenameRank(const AString & a_OldName, const AString & a_NewName);
	
	/** Renames the specified group. No action if the rank name is not found.
	Fails if the new name is already used.
	Returns true on success, false on failure. */
	bool RenameGroup(const AString & a_OldName, const AString & a_NewName);
	
	/** Sets the specified player's rank.
	If the player already had rank assigned to them, it is overwritten with the new rank.
	Note that this doesn't change the cPlayer if the player is already connected, you need to update all the
	cPlayer instances manually. */
	void SetPlayerRank(const AString & a_PlayerUUID, const AString & a_RankName);
	
	/** Sets the message visuals of an existing rank. No action if the rank name is not found. */
	void SetRankVisuals(
		const AString & a_RankName,
		const AString & a_MsgPrefix,
		const AString & a_MsgSuffix,
		const AString & a_MsgNameColorCode
	);
protected:

	SQLite::Database m_DB;
} ;




